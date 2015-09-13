#pragma once

#include <cstddef>
#include <stdlib.h>
#include <vector>
#include <memory>

#include "../types/otype.h"
#include "../types/object.h"
#include "../constants/struct_info.h"
#include "../exceptions/runtime_exception.h"

namespace elsa {
	namespace vm {

		class Heap
		{
		public:
			Heap();
			~Heap();

			Object alloc(StructInfo* si);
			void dealloc(const Object& o);
		};

	}
}