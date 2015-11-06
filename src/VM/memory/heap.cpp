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

		Object Heap::alloc_array(elsa::OType type, std::size_t size)
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

		void Heap::resize_array(Object& instance, std::size_t new_size)
		{
			assert_is_array(instance);

			auto ai = instance.gco()->ai.get();
			auto new_array = alloc_array(ai->type, new_size);
			init_array(new_array);

			copy_array(instance, new_array);

			instance.gco()->ai->num_elements = new_size;
			instance.gco()->ptr = new_array.gco()->ptr;
		}

		Object Heap::load_field(const Object& instance, FieldInfo* fi)
		{
			assert_is_struct(instance);

			auto field_ptr = get_field_ptr(instance.gco()->ptr, fi);

			switch (fi->get_type())
			{
			case Int:
				return Object(*(int*)field_ptr);
			case Float:
				return Object(*(float*)field_ptr);
			case Char:
				return Object(*(wchar_t*)field_ptr);
			case Bool:
				return Object(*(bool*)field_ptr);
			case GCOPtr:
				return Object(*(GCObject**)field_ptr);
			default:
				throw RuntimeException("Invalid field type.");
			}
		}

		Object Heap::load_field(const Object& instance, std::size_t field_index)
		{
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
			case Int:
				*(int*)field_ptr = value.i();
				break;
			case Float:
				*(float*)field_ptr = value.f();
				break;
			case Char:
				*(wchar_t*)field_ptr = value.c();
				break;
			case Bool:
				*(bool*)field_ptr = value.b();
				break;
			case GCOPtr: {
				*(GCObject**)field_ptr = value.gco();
				break;
			}
			default:
				throw RuntimeException("Invalid field type.");
			}
		}

		void Heap::store_field(const Object& instance, const Object & value, std::size_t field_index)
		{
			assert_is_struct(instance);

			auto fi = instance.gco()->si->get_field(field_index);
			store_field(instance, value, fi);
		}

		Object Heap::load_element(const Object& instance, std::size_t element_index)
		{
			assert_is_array(instance);
			assert_array_index_in_range(instance, element_index);

			auto arr = instance.gco();

			switch (arr->ai->type)
			{
			case Int:
				return Object(*((int*)arr->ptr + element_index));
			case Float:
				return Object(*((float*)arr->ptr + element_index));
			case Char:
				return Object(*((wchar_t*)arr->ptr + element_index));
			case Bool:
				return Object(*((bool*)arr->ptr + element_index));
			case GCOPtr:
				return Object(*((GCObject**)arr->ptr + element_index));
			default:
				throw RuntimeException("Invalid array type.");
			}
		}

		void Heap::store_element(const Object& instance, const Object& value, std::size_t element_index)
		{
			assert_is_array(instance);
			assert_array_index_in_range(instance, element_index);

			auto arr = instance.gco();

			switch (arr->ai->type)
			{
			case Int:
				*((int*)arr->ptr + element_index) = value.i();
				break;
			case Float:
				*((float*)arr->ptr + element_index) = value.f();
				break;
			case Char:
				*((wchar_t*)arr->ptr + element_index) = value.c();
				break;
			case Bool:
				*((bool*)arr->ptr + element_index) = value.b();
				break;
			case GCOPtr:
				*((GCObject**)arr->ptr + element_index) = value.gco();
				break;
			default:
				throw RuntimeException("Invalid array type.");
			}
		}

		std::size_t Heap::get_num_objects() const
		{
			return num_objects_;
		}

		void Heap::assert_is_struct(const Object& instance)
		{
			if (instance.get_type() != GCOPtr)
				throw RuntimeException("The instance has to be a heap allocated object");

			if (instance.gco()->type != GCObjectType::Struct)
				throw RuntimeException("Can only access fields on struct objects");
		}

		void Heap::assert_is_array(const Object& instance)
		{
			if (instance.get_type() != GCOPtr)
				throw RuntimeException("The instance has to be a heap allocated object");

			if (instance.gco()->type != GCObjectType::Array)
				throw RuntimeException("Can only access elements on array objects");
		}

		void Heap::assert_array_index_in_range(const Object& instance, std::size_t element_index)
		{
			if (element_index > instance.gco()->ai->num_elements - 1)
				throw RuntimeException("Array index out of bounds");
		}

		byte* Heap::get_field_ptr(void* s_ptr, FieldInfo* f)
		{
			byte* base_ptr = (byte*)s_ptr;

			return base_ptr + f->get_num_bytes_offset();
		}

		std::size_t Heap::get_size_of_type(elsa::OType type)
		{
			switch (type)
			{
			case Int:
				return sizeof(int);
			case Float:
				return sizeof(float);
			case Char:
				return sizeof(wchar_t);
			case Bool:
				return sizeof(bool);
			case GCOPtr:
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

		void Heap::init_array(const Object& instance)
		{
			assert_is_array(instance);

			auto array_info = instance.gco()->ai.get();
			for (std::size_t i = 0; i < array_info->num_elements; ++i)
			{
				store_element(instance, get_default_value(array_info->type), i);
			}
		}

		void Heap::copy_array(const Object& old_array, Object& new_array)
		{
			auto old_array_info = old_array.gco()->ai.get();
			auto new_array_info = new_array.gco()->ai.get();

			if(old_array_info->type != new_array_info->type)
				throw RuntimeException("Can not copy arrays of different types.");

			auto elements_to_copy = std::min(old_array_info->num_elements, new_array_info->num_elements);

			for (std::size_t i = 0; i < elements_to_copy; ++i)
			{
				auto value = load_element(old_array, i);
				store_element(new_array, value, i);
			}
		}

		Object Heap::get_default_value(elsa::OType type)
		{
			switch(type)
			{
			case Int:
				return Object(0);
			case Float:
				return Object(0.0f);
			case Char:
				return Object(L'\0');
			case Bool:
				return Object(false);
			case GCOPtr:
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