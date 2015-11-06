#pragma once

#include <memory>

#include "exceptions\codegen_exception.h"
#include "../../ast/create_struct_expression.h"
#include "vm_program.h"
#include "opcodes\opcodes.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class CreateStructExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, CreateStructExpression* expression);
		};

	}
}