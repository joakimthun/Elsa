#pragma once

#include <memory>

#include "exceptions\codegen_exception.h"
#include "../../ast/return_expression.h"
#include "vm_program.h"
#include "opcodes\opcodes.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class ReturnExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, ReturnExpression* expression);
		};

	}
}
