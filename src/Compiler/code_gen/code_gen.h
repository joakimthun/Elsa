#pragma once

#include <memory>

#include "../program.h"
#include "vm_program.h"
#include "visitors\vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		class CodeGen
		{
		public:
			CodeGen(Program* program);

			void generate();

		private:

			Program* program_;
		};

	}
}
