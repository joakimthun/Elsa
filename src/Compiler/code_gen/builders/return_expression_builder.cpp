#include "return_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void ReturnExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, ReturnExpression* expression)
		{
			expression->get_expression()->accept(visitor);
			program->emit(OpCode::ret);
		}

	}
}

