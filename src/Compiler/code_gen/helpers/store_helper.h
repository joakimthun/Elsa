#pragma once

#include <memory>

#include "exceptions\codegen_exception.h"
#include "../../ast/struct_access_expression.h"
#include "../../ast/identifier_expression.h"
#include "../../ast/assignment_expression.h"
#include "../../ast/struct_declaration_expression.h"
#include "opcodes\opcodes.h"
#include "vm_program.h"
#include "../builders/identifier_expression_builder.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class StoreHelper
		{
		public:
			static std::size_t store_field(VMProgram* program, VMExpressionVisitor* visitor, StructAccessExpression* sae);
			static std::size_t store_local(VMProgram* program, VMExpressionVisitor* visitor, IdentifierExpression* ie);
		};

	}
}
