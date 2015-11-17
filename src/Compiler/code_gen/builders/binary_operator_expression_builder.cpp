#include "binary_operator_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void BinaryOperatorExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, BinaryOperatorExpression* expression)
		{
			expression->get_left()->accept(visitor);
			expression->get_right()->accept(visitor);
			program->emit(get_operator(expression));
		}

		OpCode BinaryOperatorExpressionBuilder::get_operator(BinaryOperatorExpression* expression)
		{
			if (expression->get_type()->get_type() == OType::Int)
			{
				switch (expression->get_operator())
				{
				case TokenType::Plus:
					return OpCode::iadd;
				case TokenType::Minus:
					return OpCode::isub;
				case TokenType::Asterix:
					return OpCode::imul;
				case TokenType::Slash:
					return OpCode::idiv;
				}
			}

			if (expression->get_type()->get_type() == OType::Bool)
			{
				switch (expression->get_operator())
				{
				case TokenType::DoubleAmpersand:
					return OpCode::l_and;
				case TokenType::DoubleVerticalBar:
					return OpCode::l_or;
				}
			}

			throw CodeGenException("Unkown expression type or operator");
		}

	}
}
