#pragma once

#include <memory>

#include "exceptions\codegen_exception.h"
#include "../../ast/identifier_expression.h"
#include "constants\function_info.h"
#include "vm_program.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class IdentifierExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, IdentifierExpression* expression);
		};

	}
}