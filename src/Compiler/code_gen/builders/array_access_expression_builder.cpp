#include "array_access_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void ArrayAccessExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, ArrayAccessExpression* expression)
		{
			auto local = visitor->current_scope()->get_local(expression->get_identifier_expression()->get_name());
			auto load_inst = local->get_local_type() == LocalType::Local ? OpCode::l_local : OpCode::l_arg;

			program->emit(load_inst);
			program->emit(static_cast<int>(local->get_index()));

			expression->get_index_expression()->accept(visitor);
			program->emit(OpCode::l_ele);
		}

	}
}
