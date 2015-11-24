#pragma once

#include <memory>

#include "exceptions\codegen_exception.h"
#include "../../ast/loop_expression.h"
#include "opcodes\opcodes.h"
#include "vm_program.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class LoopExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, LoopExpression* expression);
		};

	}
}
