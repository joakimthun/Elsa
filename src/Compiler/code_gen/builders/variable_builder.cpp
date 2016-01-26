#include "variable_builder.h"
#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void VariableBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, VariableDeclarationExpression* expression)
		{
			expression->get_expression()->accept(visitor);

			program->emit(OpCode::s_local);

			auto local = visitor->current_scope()->get_local(expression->get_name());

			auto local_index = local->get_index();
			program->emit(static_cast<int>(local_index));
		}

	}
}
