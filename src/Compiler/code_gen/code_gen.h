#pragma once

#include <memory>

#include "../program.h"
#include "vm_program.h"
#include "vm_expression_visitor.h"
#include "../types/type_checker.h"

namespace elsa {
	namespace compiler {

		class CodeGen
		{
		public:
			CodeGen(Program* program, TypeChecker* type_checker);

			std::unique_ptr<VMProgram> generate();

		private:
			Program* program_;
			TypeChecker* type_checker_;
		};

	}
}
