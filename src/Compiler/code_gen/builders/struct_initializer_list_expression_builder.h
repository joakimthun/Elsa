#pragma once

#include <memory>
#include <vector>

#include "exceptions/codegen_exception.h"
#include "../../ast/struct_initializer_list_expression.h"
#include "vm_program.h"
#include "opcodes\opcodes.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class StructInitializerListExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, StructInitializerListExpression* expression);
		};

	}
}