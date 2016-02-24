#include "grouped_expression_builder.h"

#include "../vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void GroupedExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, GroupedExpression* expression)
		{
			expression->get_expression()->accept(visitor);
		}
	}
}
