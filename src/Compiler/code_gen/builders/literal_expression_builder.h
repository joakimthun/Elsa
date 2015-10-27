#pragma once

#include <memory>

#include "exceptions\codegen_exception.h"
#include "../../ast/integer_literal_expression.h"
#include "opcodes\opcodes.h"
#include "vm_program.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class LiteralExpressionBuilder
		{
		public:
			static void build(VMProgram* program, IntegerLiteralExpression* expression);
		};

	}
}