#pragma once

#include <memory>

#include "exceptions\codegen_exception.h"
#include "../../ast/postfix_operator_expression.h"
#include "opcodes\opcodes.h"
#include "vm_program.h"
#include "../helpers/store_helper.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class PostfixOperatorExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, PostfixOperatorExpression* expression);

		private:
			static void build_operator(TokenType op, VMProgram* program, PostfixOperatorExpression* expression);
		};

	}
}
