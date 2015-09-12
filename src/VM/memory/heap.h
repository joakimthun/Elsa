#pragma once

#include <cstddef>
#include <stdlib.h>
#include <vector>
#include <memory>

#include "../constants/struct_info.h"
#include "../exceptions/runtime_exception.h"

namespace elsa {
	namespace vm {

		class Heap
		{
		public:
			Heap();
			~Heap();

			void* alloc(const StructInfo* type);
		private:

			std::vector<void*> objects_;
		};

	}
}