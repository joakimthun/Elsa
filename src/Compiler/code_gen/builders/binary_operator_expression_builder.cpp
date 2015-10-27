#include "binary_operator_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void BinaryOperatorExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, BinaryOperatorExpression* expression)
		{
			expression->get_left()->accept(visitor);
			expression->get_right()->accept(visitor);
		}

		OpCode BinaryOperatorExpressionBuilder::get_operator(BinaryOperatorExpression* expression)
		{
			if (expression->get_type()->get_type() == OType::Int)
			{
				switch (expression->get_operator())
				{

				}
			}

			throw CodeGenException("Unkown expression type or operator");
		}

	}
}
