#include "literal_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void LiteralExpressionBuilder::build(VMProgram* program, IntegerLiteralExpression* expression)
		{
			program->emit(OpCode::iconst);
			program->emit(expression->get_value());
		}

	}
}

