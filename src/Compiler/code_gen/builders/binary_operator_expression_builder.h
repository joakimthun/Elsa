#pragma once

#include <memory>

#include "exceptions\codegen_exception.h"
#include "../../ast/binary_operator_expression.h"
#include "opcodes\opcodes.h"
#include "vm_program.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class BinaryOperatorExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, BinaryOperatorExpression* expression, TokenType* op_override = nullptr);

		private:
			static void build_operator(TokenType op, VMProgram* program, VMExpressionVisitor* visitor, BinaryOperatorExpression* expression);
		};

	}
}