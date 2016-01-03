#pragma once

#include <memory>

#include "exceptions\codegen_exception.h"
#include "../../ast/struct_access_expression.h"
#include "opcodes\opcodes.h"
#include "vm_program.h"
#include "identifier_expression_builder.h"
#include "func_call_expression_builder.h"

namespace elsa {
	namespace compiler {

		class StructAccessExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, StructAccessExpression* expression);
		};

	}
}