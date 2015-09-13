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
	}
}