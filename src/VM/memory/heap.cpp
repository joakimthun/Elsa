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
			int* iptr = (int*)ptr;
			*iptr = 12;
			iptr++;
			*iptr = 24;

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
			if (instance.get_type() != GCOPtr)
				throw RuntimeException("Can only load fields from heap allocated objects");

			byte* base_ptr = (byte*)instance.gco()->ptr;
			auto f = instance.gco()->si->get_field(field_index);

			byte* field_start = base_ptr + f->get_num_bytes_offset();

			switch (f->get_type())
			{
			case Int:
				return Object(*(int*)field_start);
			case Float:
				return Object(*(float*)field_start);
			case Char:
				return Object(*(wchar_t*)field_start);
			case Bool:
				return Object(*(bool*)field_start);
				//case GCOPtr:
				//	size_ += sizeof(int*);
				//	break;
			default:
				throw RuntimeException("Invalid field type.");
			}
		}

		void Heap::store_field(const Object & instance, const Object & value, std::size_t field_index)
		{

		}
	}
}