#include "binary_operator_expression_builder.h"

#include "../vm_expression_visitor.h"

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

			if (expression->get_type()->get_type() == ObjectType::Float)
			{
				switch (op)
				{
				case TokenType::Plus:
					program->emit(OpCode::fadd);
					return;
				case TokenType::Minus:
					program->emit(OpCode::fsub);
					return;
				case TokenType::Asterix:
					program->emit(OpCode::fmul);
					return;
				case TokenType::Slash:
					program->emit(OpCode::fdiv);
					return;
				}
			}

			if (expression->get_type()->get_type() == ObjectType::Bool)
			{
				// We expect the left and right expressions to be of the same type here, if they are not, we are missing some type checking
				auto type = std::unique_ptr<ElsaType>(visitor->type_checker()->get_expression_type(expression->get_left()));

				switch (type->get_type())
				{
				case ObjectType::Int: {
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
				case ObjectType::Float: {
					switch (op)
					{
					case TokenType::DoubleEquals:
						program->emit(OpCode::feq);
						return;
					case TokenType::NotEquals:
						program->emit(OpCode::fneq);
						return;
					case TokenType::LessThan:
						program->emit(OpCode::flt);
						return;
					case TokenType::GreaterThan:
						program->emit(OpCode::fgt);
						return;
					case TokenType::LessThanEquals: {
						program->emit(OpCode::flt);
						auto op_override = TokenType::DoubleEquals;
						build(program, visitor, expression, &op_override);
						program->emit(OpCode::ior);
						return;
					}
					case TokenType::GreaterThanEquals: {
						program->emit(OpCode::fgt);
						auto op_override = TokenType::DoubleEquals;
						build(program, visitor, expression, &op_override);
						program->emit(OpCode::ior);
						return;
					}
					}
				case ObjectType::Char: {
					switch (op)
					{
					case TokenType::DoubleEquals:
						program->emit(OpCode::ceq);
						return;
					case TokenType::NotEquals:
						program->emit(OpCode::cneq);
						return;
					}
				}
				case ObjectType::Bool: {
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
					}
				}
				case ObjectType::GCOPtr: {
					if (type->get_struct_declaration_expression() != nullptr)
					{
						const auto eq_fi = program->get_struct(type->get_struct_declaration_expression()->get_name(true))->get_function(L"Equals");
						auto neq_fi = visitor->native_function_table().get(L"Equals");

						OpCode callop;
						int function_index;
						if (eq_fi != nullptr)
						{
							callop = OpCode::call;
							function_index = static_cast<int>(eq_fi->get_addr());
						}
						else
						{
							callop = OpCode::ncall;
							function_index = static_cast<int>(neq_fi->get_index());
						}

						switch (op)
						{
						case TokenType::DoubleEquals: {
							program->emit(callop);
							program->emit(function_index);
							return;
						}
						case TokenType::NotEquals: {
							program->emit(callop);
							program->emit(function_index);
							program->emit(OpCode::iconst);
							program->emit(0);
							program->emit(OpCode::ieq);
							return;
						}
						}
					}
				}
				default:
					break;
				}
				}

				throw CodeGenException("Unkown expression type or operator");
			}

		}
	}
}
