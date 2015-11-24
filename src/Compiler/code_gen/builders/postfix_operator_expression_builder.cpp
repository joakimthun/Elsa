#include "postfix_operator_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void PostfixOperatorExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, PostfixOperatorExpression* expression)
		{
			expression->get_expression()->accept(visitor);
			build_operator(expression->get_operator(), program, expression);
		}

		void PostfixOperatorExpressionBuilder::build_operator(TokenType op, VMProgram* program, PostfixOperatorExpression* expression)
		{
			if (expression->get_type()->get_type() == ObjectType::Int)
			{
				switch (op)
				{
				case TokenType::PlusPlus:
					program->emit(OpCode::iconst);
					program->emit(1);
					program->emit(OpCode::iadd);
					return;
				case TokenType::MinusMinus:
					program->emit(OpCode::iconst);
					program->emit(1);
					program->emit(OpCode::isub);
					return;
				}
			}

			throw CodeGenException("Unkown expression type or operator");
		}

	}
}
