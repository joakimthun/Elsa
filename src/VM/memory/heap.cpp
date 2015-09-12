#include "heap.h"

namespace elsa {
	namespace vm {

		Heap::Heap() {}
		Heap::~Heap() {}

		void* Heap::alloc(const StructInfo* type)
		{
			auto ptr = malloc(type->get_size());

			if (ptr == nullptr)
			{
				throw RuntimeException("Memory allocation failed for type: " + type->get_name());
			}

			objects_.push_back(ptr);

			return ptr;
		}
	}
}