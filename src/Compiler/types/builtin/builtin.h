#pragma once

#include <vector>
#include <memory>
#include <utility>

#include "vm_program.h"
#include "../../symbol_tables/struct_table.h"

#include "array.h"

namespace elsa {
	namespace compiler {

		class Builtin
		{
		public:
			static void init(VMProgram* program);
			static void init(StructTable* table);
		};
	}
}
