#pragma once

#include <memory>

#include "exceptions\codegen_exception.h"
#include "../../ast/struct_access_expression.h"
#include "../../ast/identifier_expression.h"
#include "../../ast/assignment_expression.h"
#include "../../ast/array_access_expression.h"
#include "opcodes\opcodes.h"
#include "vm_program.h"
#include "identifier_expression_builder.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class AssignmentExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, AssignmentExpression* expression);

		private:
			static void build_initializer_list(Expression* exp, std::size_t index, VMProgram* program, VMExpressionVisitor* visitor, OpCode load_inst);
			static bool is_initializer_list(Expression* exp);
		};

	}
}
