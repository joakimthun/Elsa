#pragma once

#include <memory>
#include <utility>

#include "exceptions\codegen_exception.h"
#include "../../ast/struct_declaration_expression.h"
#include "constants\struct_info.h"
#include "constants\function_info.h"
#include "vm_program.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class StructDeclarationExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, StructDeclarationExpression* expression);
		};

	}
}