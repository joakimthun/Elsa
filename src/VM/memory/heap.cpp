#include "heap.h"

namespace elsa {
	namespace vm {

		Heap::Heap() 
		{}

		Heap::~Heap() {}

		Object Heap::alloc_struct(StructInfo* si)
		{
			auto ptr = malloc(si->get_size());

			if (ptr == nullptr)
			{
				throw RuntimeException("Memory allocation failed for type: " + si->get_name());
			}

			auto gco = new GCObject(GCObjectType::Struct);
			gco->si = si;
			gco->ptr = ptr;

			auto obj =  Object(gco);
			init_struct(obj);

			return obj;
		}

		Object Heap::alloc_array(OType type, std::size_t size)
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

			auto obj = Object(gco);
			init_array(obj);

			return obj;
		}

		void Heap::realloc_array(Object& instance, std::size_t new_size)
		{

		}

		void Heap::dealloc(Object& o)
		{
			if(o.get_type() != GCOPtr)
				throw RuntimeException("Can only deallocate memory for heap allocated objects");

			delete o.gco();
			o.set_type(OType::Null);
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

		std::size_t Heap::get_size_of_type(OType type)
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

		Object Heap::get_default_value(OType type)
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
	}
}