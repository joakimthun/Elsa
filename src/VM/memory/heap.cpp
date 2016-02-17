#include "heap.h"

namespace elsa {
	namespace vm {

		Heap::Heap() 
			:
			num_objects_(0),
			base_(nullptr)
		{}

		Heap::~Heap() {}

		Object Heap::alloc_struct(const StructInfo* si)
		{
			auto ptr = malloc(si->get_size());

			if (ptr == nullptr)
			{
				throw RuntimeException("The struct memory allocation failed");
			}

			auto gco = new GCObject(GCObjectType::Struct);
			gco->si = si;
			gco->ptr = ptr;

			link_new_object(gco);
			increment_num_objects();

			auto obj =  Object(gco);
			init_struct(obj);

			return obj;
		}

		Object Heap::alloc_array(elsa::VMType type, std::size_t size)
		{
			auto element_size = get_size_of_type(type);
			auto array_size = element_size * size;

			auto ptr = malloc(array_size);

			if (ptr == nullptr)
			{
				throw RuntimeException("Array memory allocation failed");
			}

			auto gco = new GCObject(GCObjectType::Array);
			gco->ptr = ptr;
			gco->ai = std::unique_ptr<ArrayInfo>(new ArrayInfo(type, size, element_size));

			link_new_object(gco);
			increment_num_objects();

			auto obj = Object(gco);
			init_array(obj);

			return obj;
		}

		Object Heap::load_field(const Object& instance, FieldInfo* fi)
		{
			assert_is_struct(instance);

			auto field_ptr = get_field_ptr(instance.gco()->ptr, fi);

			switch (fi->get_type())
			{
			case VMType::Int:
				return Object(*(int*)field_ptr);
			case VMType::Float:
				return Object(*(float*)field_ptr);
			case VMType::Char:
				return Object(*(wchar_t*)field_ptr);
			case VMType::GCOPtr:
				return Object(*(GCObject**)field_ptr);
			default:
				throw RuntimeException("Invalid field type.");
			}
		}

		Object Heap::load_field(const Object& instance, std::size_t field_index)
		{
			assert_is_not_null(instance);
			assert_is_struct(instance);

			auto fi = instance.gco()->si->get_field(field_index);
			return load_field(instance, fi);
		}

		void Heap::store_field(const Object& instance, const Object& value, FieldInfo* fi)
		{
			assert_is_struct(instance);

			auto field_ptr = get_field_ptr(instance.gco()->ptr, fi);

			switch (fi->get_type())
			{
			case VMType::Int:
				*(int*)field_ptr = value.i();
				break;
			case VMType::Float:
				*(float*)field_ptr = value.f();
				break;
			case VMType::Char:
				*(wchar_t*)field_ptr = value.c();
				break;
			case VMType::GCOPtr: {
				*(GCObject**)field_ptr = value.gco();
				break;
			}
			default:
				throw RuntimeException("Invalid field type.");
			}
		}

		void Heap::store_field(const Object& instance, const Object & value, std::size_t field_index)
		{
			assert_is_not_null(instance);
			assert_is_struct(instance);

			auto fi = instance.gco()->si->get_field(field_index);
			store_field(instance, value, fi);
		}

		Object Heap::load_element(const Object& instance, int element_index)
		{
			assert_is_array(instance);
			assert_array_index_in_range(instance, element_index);

			auto arr = instance.gco();

			switch (arr->ai->type)
			{
			case VMType::Int:
				return Object(*((int*)arr->ptr + element_index));
			case VMType::Float:
				return Object(*((float*)arr->ptr + element_index));
			case VMType::Char:
				return Object(*((wchar_t*)arr->ptr + element_index));
			case VMType::GCOPtr:
				return Object(*((GCObject**)arr->ptr + element_index));
			default:
				throw RuntimeException("Invalid array type.");
			}
		}

		void Heap::store_element(const Object& instance, const Object& value, int element_index)
		{
			assert_is_array(instance);
			assert_array_index_in_range(instance, element_index);

			auto arr = instance.gco();

			switch (arr->ai->type)
			{
			case VMType::Int:
				*((int*)arr->ptr + element_index) = value.i();
				break;
			case VMType::Float:
				*((float*)arr->ptr + element_index) = value.f();
				break;
			case VMType::Char:
				*((wchar_t*)arr->ptr + element_index) = value.c();
				break;
			case VMType::GCOPtr:
				*((GCObject**)arr->ptr + element_index) = value.gco();
				break;
			default:
				throw RuntimeException("Invalid array type.");
			}
		}

		void Heap::add_element(Object& instance, const Object& value)
		{
			assert_is_array(instance);

			auto& ai = instance.gco()->ai;
			if (ai->next_index > ai->num_elements - 1)
				resize_array(instance, ai->num_elements * 2);

			store_element(instance, value, static_cast<int>(ai->next_index++));
		}

		Object Heap::pop_element(Object& instance)
		{
			assert_is_array(instance);
			auto& ai = instance.gco()->ai;
			auto last_element_index = ai->next_index - 1;

			auto popped_element = load_element(instance, static_cast<int>(last_element_index));
			remove_element(instance, static_cast<int>(last_element_index));
			return popped_element;
		}

		void Heap::remove_element(Object& instance, int element_index)
		{
			assert_is_array(instance);
			assert_array_index_in_range(instance, element_index);

			auto& ai = instance.gco()->ai;

			auto new_array = alloc_array(ai->type, ai->next_index);
			copy_array(instance, new_array, element_index);
			instance.gco()->swap_array(new_array.gco()->ptr, new_array.gco()->ai.release());
		}

		void Heap::copy_array(const Object& source, Object& target, int index_to_exclude)
		{
			assert_is_array(source);
			assert_is_array(target);
			assert_arrays_are_same_type(source, target);

			const auto& source_info = source.gco()->ai;
			auto& target_info = target.gco()->ai;
			target_info->next_index = 0;

			for (int i = 0; i < source_info->next_index; i++)
			{
				if (i == index_to_exclude)
					continue;

				add_element(target, load_element(source, i));
			}
		}

		int Heap::array_length(const Object& instance)
		{
			assert_is_array(instance);
			return static_cast<int>(instance.gco()->ai->next_index);
		}

		std::size_t Heap::get_num_objects() const
		{
			return num_objects_;
		}

		Object Heap::allocate_resource_handle(ResourceHandle* handle)
		{
			auto gco = new GCObject(GCObjectType::RHandle);
			gco->resource_handle_ = handle;
			return Object(gco);
		}

		void Heap::assert_is_not_null(const Object& instance)
		{
			if (instance.get_type() != VMType::GCOPtr)
				throw RuntimeException("The instance has to be a heap allocated object");

			if (instance.gco() == nullptr)
				throw RuntimeException("Nullptr exception");
		}

		void Heap::assert_is_struct(const Object& instance)
		{
			if (instance.get_type() != VMType::GCOPtr)
				throw RuntimeException("The instance has to be a heap allocated object");

			if (instance.gco()->type != GCObjectType::Struct)
				throw RuntimeException("Can only access fields on struct objects");
		}

		void Heap::assert_is_array(const Object& instance)
		{
			assert_is_not_null(instance);

			if (instance.get_type() != VMType::GCOPtr)
				throw RuntimeException("The instance has to be a heap allocated object");

			if (instance.gco()->type != GCObjectType::Array)
				throw RuntimeException("Can only access elements on array objects");
		}

		void Heap::assert_arrays_are_same_type(const Object& first, const Object& second)
		{
			if(first.gco()->ai->type != second.gco()->ai->type)
				throw RuntimeException("The passed arrays are not of the same type");
		}

		void Heap::assert_array_index_in_range(const Object& instance, int element_index)
		{
			if (element_index < 0 || element_index >= instance.gco()->ai->next_index)
				throw RuntimeException("Array index out of bounds");
		}

		byte* Heap::get_field_ptr(void* s_ptr, FieldInfo* f)
		{
			byte* base_ptr = (byte*)s_ptr;

			return base_ptr + f->get_num_bytes_offset();
		}

		std::size_t Heap::get_size_of_type(elsa::VMType type)
		{
			switch (type)
			{
			case VMType::Int:
				return sizeof(int);
			case VMType::Float:
				return sizeof(float);
			case VMType::Char:
				return sizeof(wchar_t);
			case VMType::GCOPtr:
				return sizeof(GCObject*);
			default:
				throw RuntimeException("Invalid type.");
			}
		}

		void Heap::init_struct(const Object& instance)
		{
			assert_is_struct(instance);

			auto gco = instance.gco();
			for (auto& field : gco->si->get_fields())
			{
				store_field(instance, get_default_value(field->get_type()), field.get());
			}
		}

		void Heap::init_array(const Object& instance, std::size_t start_index)
		{
			assert_is_array(instance);

			auto array_info = instance.gco()->ai.get();
			for (std::size_t i = start_index; i < array_info->next_index; ++i)
			{
				store_element(instance, get_default_value(array_info->type), static_cast<int>(i));
			}
		}

		void Heap::resize_array(Object& instance, std::size_t new_size)
		{
			assert_is_array(instance);

			auto ai = instance.gco()->ai.get();

			auto new_array_size = new_size * ai->element_size;
			instance.gco()->ptr = realloc(instance.gco()->ptr, new_array_size);

			auto old_size = instance.gco()->ai->num_elements;
			instance.gco()->ai->num_elements = new_size;

			init_array(instance, old_size);
		}

		Object Heap::get_default_value(elsa::VMType type)
		{
			switch(type)
			{
			case VMType::Int:
				return Object(0);
			case VMType::Float:
				return Object(0.0f);
			case VMType::Char:
				return Object(L'\0');
			case VMType::GCOPtr:
				return Object(nullptr);
			default:
				throw RuntimeException("Invalid type.");
			}
		}

		void Heap::link_new_object(GCObject* obj)
		{
			// Keep a linked list of all heap allocated objects so the gc can delete them even if they are not reachable by the vm itself
			obj->next = base_;
			base_ = obj;
		}

		void Heap::increment_num_objects()
		{
			num_objects_++;
		}
	}
}