#include "identifier_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void IdentifierExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, IdentifierExpression* expression)
		{
			program->emit(OpCode::l_local);

			auto local = visitor->get_local(expression->get_name());

			program->emit(static_cast<int>(local->get_index()));
		}

	}
}
