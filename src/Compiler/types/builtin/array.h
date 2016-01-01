#pragma once

#include <vector>
#include <memory>
#include <utility>

#include "vm_program.h"
#include "constants\struct_info.h"
#include "../../symbol_tables/struct_table.h"
#include "../../ast/func_declaration_expression.h"

namespace elsa {
	namespace compiler {

		class Array
		{
		public:
			static void init(VMProgram* program);
			static void init(StructTable* table);

		private:
			static void build_info(VMProgram* program);
			static void build_symbol(StructTable* table);
		};
	}
}
