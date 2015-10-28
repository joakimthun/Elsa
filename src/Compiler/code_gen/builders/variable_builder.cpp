#include "variable_builder.h"
#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void VariableBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, VariableDeclarationExpression* expression)
		{
			if (visitor->current_scope_has_entry(expression->get_name()))
				throw CodeGenException("A variable with the same name has already been declared in the current scope");

			visitor->push_current_scope(expression->get_name(), *expression->get_type());
			visitor->get_current_function()->increment_num_locals();

			expression->get_expression()->accept(visitor);

			program->emit(OpCode::s_local);

			auto local = visitor->get_from_current_scope(expression->get_name());

			program->emit(static_cast<int>(local->get_index()));
		}

	}
}
