#pragma once

#include <memory>
#include <utility>

#include "exceptions\codegen_exception.h"
#include "../../ast/array_access_expression.h"
#include "vm_program.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class ArrayAccessExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, ArrayAccessExpression* expression);
		};

	}
}
