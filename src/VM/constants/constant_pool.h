#pragma once

#include <memory>
#include <vector>
#include <cstddef>

#include "../exceptions/elsa_exception.h"
#include "constant_entry.h"
#include "function_info.h"
#include "struct_info.h"

namespace elsa {
	namespace vm {

		class ConstantPool
		{
		public:
			ConstantPool();
			~ConstantPool();

			void add_entry(ConstantEntry* entry);
			FunctionInfo* get_func_at(std::size_t addr);
			StructInfo* get_struct_at(std::size_t index);

		private:
			std::vector<std::unique_ptr<ConstantEntry>> entries_;
		};

	}
}
