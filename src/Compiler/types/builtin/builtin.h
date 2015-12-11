#pragma once

#include <vector>
#include <memory>
#include <utility>

#include "vm_program.h"
#include "constants\struct_info.h"

namespace elsa {
	namespace compiler {

		class Builtin
		{
		public:
			static void init(VMProgram* program);

		private:
			static void build_array(VMProgram* program);
		};
	}
}
