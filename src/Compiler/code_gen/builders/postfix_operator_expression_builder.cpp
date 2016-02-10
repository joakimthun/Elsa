#include "postfix_operator_expression_builder.h"

#include "../vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void PostfixOperatorExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, PostfixOperatorExpression* expression)
		{
			if (auto sae = dynamic_cast<StructAccessExpression*>(expression->get_expression()))
			{
				auto field_index = LoadHelper::load_field(program, visitor, sae);
				LoadHelper::load_field(program, visitor, sae, true);
				build_operator(expression->get_operator(), program, expression);
				program->emit(OpCode::s_field);
				program->emit(static_cast<int>(field_index));
				return;
			}

			if (auto ie = dynamic_cast<IdentifierExpression*>(expression->get_expression()))
			{
				auto local_index = LoadHelper::load_local(program, visitor, ie);
				build_operator(expression->get_operator(), program, expression);
				program->emit(OpCode::s_local);
				program->emit(static_cast<int>(local_index));

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
