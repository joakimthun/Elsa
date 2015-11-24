#include "postfix_operator_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void PostfixOperatorExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, PostfixOperatorExpression* expression)
		{
			expression->get_expression()->accept(visitor);
			build_operator(expression->get_operator(), program, expression);

			if (auto ie = dynamic_cast<IdentifierExpression*>(expression->get_expression()))
			{
				auto local = visitor->current_scope()->get_local(ie->get_name());
				program->emit(OpCode::s_local);
				program->emit(static_cast<int>(local->get_index()));

				return;
			}

			throw CodeGenException("Not supported -> PostfixOperatorExpressionBuilder");
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
