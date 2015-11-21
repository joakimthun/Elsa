#include "binary_operator_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void BinaryOperatorExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, BinaryOperatorExpression* expression, TokenType* op_override)
		{
			expression->get_left()->accept(visitor);
			expression->get_right()->accept(visitor);

			auto op = expression->get_operator();

			if (op_override != nullptr)
				op = *op_override;

			build_operator(op, program, visitor, expression);
		}

		void BinaryOperatorExpressionBuilder::build_operator(TokenType op, VMProgram* program, VMExpressionVisitor* visitor, BinaryOperatorExpression* expression)
		{
			if (expression->get_type()->get_type() == ObjectType::Int)
			{
				switch (op)
				{
					case TokenType::Plus:
						program->emit(OpCode::iadd);
						return;
					case TokenType::Minus:
						program->emit(OpCode::isub);
						return;
					case TokenType::Asterix:
						program->emit(OpCode::imul);
						return;
					case TokenType::Slash:
						program->emit(OpCode::idiv);
						return;
				}
			}

			if (expression->get_type()->get_type() == ObjectType::Bool)
			{
				switch (op)
				{
					case TokenType::DoubleEquals:
						program->emit(OpCode::ieq);
						return;
					case TokenType::NotEquals:
						program->emit(OpCode::ineq);
						return;
					case TokenType::DoubleAmpersand:
						program->emit(OpCode::iand);
						return;
					case TokenType::DoubleVerticalBar:
						program->emit(OpCode::ior);
						return;
					case TokenType::LessThan:
						program->emit(OpCode::ilt);
						return;
					case TokenType::GreaterThan:
						program->emit(OpCode::igt);
						return;
					case TokenType::LessThanEquals: {
						program->emit(OpCode::ilt);
						auto op_override = TokenType::DoubleEquals;
						build(program, visitor, expression, &op_override);
						program->emit(OpCode::ior);
						return;
					}
					case TokenType::GreaterThanEquals: {
						program->emit(OpCode::igt);
						auto op_override = TokenType::DoubleEquals;
						build(program, visitor, expression, &op_override);
						program->emit(OpCode::ior);
						return;
					}
				}
			}

			throw CodeGenException("Unkown expression type or operator");
		}

	}
}
