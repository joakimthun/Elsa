#pragma once

#include <memory>
#include <vector>

#include "exceptions/codegen_exception.h"
#include "../../ast/grouped_expression.h"
#include "vm_program.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class GroupedExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, GroupedExpression* expression);
		};

	}
}