#include "type_cast_expression_builder.h"

#include "../vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void TypeCastExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, TypeCastExpression* expression)
		{
			expression->get_expression()->accept(visitor);
			program->emit(OpCode::t_cast);
			program->emit(static_cast<int>(expression->get_dest_type()->get_vm_type()));
		}

	}
}
