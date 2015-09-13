#include "heap.h"

namespace elsa {
	namespace vm {

		Heap::Heap() {}
		Heap::~Heap() {}

		Object Heap::alloc(StructInfo* si)
		{
			auto ptr = malloc(si->get_size());

			if (ptr == nullptr)
			{
				throw RuntimeException("Memory allocation failed for type: " + si->get_name());
			}

			// Just for testing load_field()
			//int* iptr = (int*)ptr;
			//*iptr = 12;
			//iptr++;
			//*iptr = 24;

			auto gco = new GCObject;
			gco->si = si;
			gco->ptr = ptr;

			return Object(gco);
		}

		void Heap::dealloc(const Object& o)
		{
			if(o.get_type() != GCOPtr)
				throw RuntimeException("Can only deallocate memory for heap allocated objects");

			delete o.gco();
		}

		Object Heap::load_field(const Object & instance, std::size_t field_index)
		{
			assert_is_gcoptr(instance);

			auto f = instance.gco()->si->get_field(field_index);
			auto field_ptr = get_field_ptr(instance.gco()->ptr, f);

			switch (f->get_type())
			{
			case Int:
				return Object(*(int*)field_ptr);
			case Float:
				return Object(*(float*)field_ptr);
			case Char:
				return Object(*(wchar_t*)field_ptr);
			case Bool:
				return Object(*(bool*)field_ptr);
			//case GCOPtr:
			//	size_ += sizeof(int*);
			//	break;
			default:
				throw RuntimeException("Invalid field type.");
			}
		}

		void Heap::store_field(const Object & instance, const Object & value, std::size_t field_index)
		{
			assert_is_gcoptr(instance);

			auto f = instance.gco()->si->get_field(field_index);
			auto field_ptr = get_field_ptr(instance.gco()->ptr, f);

			switch (f->get_type())
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
				//case GCOPtr:
				//	size_ += sizeof(int*);
				//	break;
			default:
				throw RuntimeException("Invalid field type.");
			}
		}

		void Heap::assert_is_gcoptr(const Object & instance)
		{
			if (instance.get_type() != GCOPtr)
				throw RuntimeException("Can only load fields from heap allocated objects");
		}

		byte* Heap::get_field_ptr(void* s_ptr, FieldInfo* f)
		{
			byte* base_ptr = (byte*)s_ptr;

			return base_ptr + f->get_num_bytes_offset();
		}
	}
}