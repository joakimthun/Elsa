#pragma once

#include <memory>

#include "exceptions\codegen_exception.h"
#include "../../ast/variable_declaration_expression.h"
#include "../../ast/string_literal_expression.h"
#include "../../ast/func_declaration_expression.h"
#include "vm_program.h"
#include "opcodes\opcodes.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class VariableBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, VariableDeclarationExpression* expression);
		};

	}
}