#pragma once

#include <memory>

#include "exceptions\codegen_exception.h"
#include "../../ast/type_cast_expression.h"
#include "constants\function_info.h"
#include "vm_program.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class TypeCastExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, TypeCastExpression* expression);
		};

	}
}