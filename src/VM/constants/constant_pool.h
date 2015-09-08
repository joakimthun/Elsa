#pragma once

#include <memory>
#include <vector>
#include <cstddef>

#include "constant_entry.h"
#include "function_entry.h"

namespace elsa {
	namespace vm {

		class ConstantPool
		{
		public:
			ConstantPool();
			~ConstantPool();

			void add_entry(ConstantEntry* entry);
			FunctionEntry* get_func_at(std::size_t addr);
		private:
			std::vector<std::unique_ptr<ConstantEntry>> entries_;
		};

	}
}
