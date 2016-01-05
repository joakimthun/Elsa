#include "type_checker.h"

#include "../parsing/elsa_parser.h"

namespace elsa {
	namespace compiler {
		TypeChecker::TypeChecker(ElsaParser* parser)
			:
			parser_(parser)
		{
		}

		ElsaType* TypeChecker::get_expression_type(Expression* expression)
		{
			if (is_of_type<BinaryOperatorExpression>(expression))
			{
				auto be = static_cast<BinaryOperatorExpression*>(expression);

				if (!is_same_type(be->get_left(), be->get_right()))
				{
					throw ParsingException("Type mismatch");
				}

				if (is_boolean_operator(be->get_operator()))
				{
					return new ElsaType(ObjectType::Bool);
				}

				return get_expression_type(be->get_left());
			}
			if (is_of_type<IdentifierExpression>(expression))
			{
				auto id = static_cast<IdentifierExpression*>(expression);
				auto local = parser_->current_scope()->get_local(id->get_name());

				if (local == nullptr)
					throw ParsingException("Unkown identifier");

				if (local->get_struct_expression() != nullptr)
				{
					return new ElsaType(local->get_struct_expression());
				}
				else
				{
					return new ElsaType(local->get_type());
				}
			}
			if (is_of_type<PrefixOperatorExpression>(expression))
			{
				auto poe = static_cast<PrefixOperatorExpression*>(expression);
				return get_expression_type(poe->get_right());
			}
			if (is_of_type<IntegerLiteralExpression>(expression))
			{
				return new ElsaType(ObjectType::Int);
			}
			if (is_of_type<FloatLiteralExpression>(expression))
			{
				return new ElsaType(ObjectType::Float);
			}
			if (is_of_type<CharLiteralExpression>(expression))
			{
				return new ElsaType(ObjectType::Char);
			}
			if (is_of_type<BoolLiteralExpression>(expression))
			{
				return new ElsaType(ObjectType::Bool);
			}
			if (is_of_type<CreateStructExpression>(expression))
			{
				auto cse = static_cast<CreateStructExpression*>(expression);
				return new ElsaType(cse->get_type()->get_struct_declaration_expression());
			}
			if (is_of_type<FieldAccessExpression>(expression))
			{
				auto fae = static_cast<FieldAccessExpression*>(expression);
				auto local = parser_->current_scope()->get_local(fae->get_name());

				if (local == nullptr)
					throw ParsingException("Invalid field name");

				if (local->get_struct_expression() != nullptr)
				{
					return new ElsaType(local->get_struct_expression());
				}
				{
					return new ElsaType(local->get_type());
				}
			}
			if (is_of_type<StructAccessExpression>(expression))
			{
				auto sae = static_cast<StructAccessExpression*>(expression);
				auto current = sae->get_base()->get_type()->get_struct_declaration_expression();
				std::unique_ptr<ElsaType> type;

				for (const auto& field_expression : sae->get_expressions())
				{
					type.reset(get_access_type(current, field_expression->get_name()));

					if (field_expression->get_type()->get_type() == ObjectType::GCOPtr)
						current = field_expression->get_type()->get_struct_declaration_expression();
				}

				return type.release();
			}
			if (is_of_type<ArgumentExpression>(expression))
			{
				auto ae = static_cast<ArgumentExpression*>(expression);
				return new ElsaType(ae->get_type());
			}
			if (is_of_type<VariableDeclarationExpression>(expression))
			{
				auto vde = static_cast<VariableDeclarationExpression*>(expression);
				return new ElsaType(vde->get_type());
			}
			if (is_of_type<FuncCallExpression>(expression))
			{
				auto fde = static_cast<FuncCallExpression*>(expression);
				return new ElsaType(fde->get_func_declaration_expression()->get_return_type());
			}
			if (is_of_type<ReturnExpression>(expression))
			{
				auto re = static_cast<ReturnExpression*>(expression);
				return new ElsaType(re->get_type());
			}
			if (is_of_type<ArrayDeclarationExpression>(expression))
			{
				auto ade = static_cast<ArrayDeclarationExpression*>(expression);
				return new ElsaType(ade->get_type(), true);
			}

			throw ParsingException("Unkown expression type.");
		}

		ElsaType* TypeChecker::get_type_from_token(Token* token)
		{
			auto type = token->get_type();
			switch (type)
			{
			case TokenType::Void: {
				return new ElsaType(ObjectType::Void);
			}
			case TokenType::Int: {
				return new ElsaType(ObjectType::Int);
			}
			case TokenType::Float: {
				return new ElsaType(ObjectType::Float);
			}
			case TokenType::Char: {
				return new ElsaType(ObjectType::Char);
			}
			case TokenType::Bool: {
				return new ElsaType(ObjectType::Bool);
			}
			case TokenType::IntegerLiteral: {
				return new ElsaType(ObjectType::Int);
			}
			case TokenType::FloatLiteral: {
				return new ElsaType(ObjectType::Float);
			}
			case TokenType::CharLiteral: {
				return new ElsaType(ObjectType::Char);
			}
			case TokenType::BoolLiteral: {
				return new ElsaType(ObjectType::Bool);
			}
			case TokenType::Identifier: {
				return get_struct_type(token->get_value());
			}
			default:
				throw ParsingException("Invalid type.");
			}
		}

		void TypeChecker::assert_is_same_type(ObjectType t1, ObjectType t2)
		{
			if (t1 != t2)	
				throw ParsingException("Type mismatch");
		}

		bool TypeChecker::is_same_type(Expression* first, Expression* second)
		{
			auto left = get_expression_type(first);
			auto right = get_expression_type(second);

			return is_same_type(left, right);
		}

		bool TypeChecker::is_same_type(const ElsaType* first, const ElsaType* second)
		{
			if (first->get_type() == ObjectType::GCOPtr && second->get_type() == ObjectType::GCOPtr)
				return first->get_struct_declaration_expression()->get_name() == second->get_struct_declaration_expression()->get_name();

			return first->get_type() == second->get_type();
		}

		ElsaType* TypeChecker::get_access_type(const StructDeclarationExpression* struct_expression, const std::wstring& name)
		{
			if(struct_expression == nullptr)
				throw ParsingException("The StructDeclarationExpression can not be a nullptr");

			for (const auto& declared_field : struct_expression->get_fields())
			{
				if (declared_field->get_name() == name)
					return new ElsaType(declared_field->get_type());
			}

			for (const auto& function : struct_expression->get_functions())
			{
				if (function->get_name() == name)
					return new ElsaType(function.get());
			}

			throw ParsingException("Invalid struct field or function");
		}

		ElsaType* TypeChecker::get_struct_type(const std::wstring& name)
		{
			if (parser_->struct_table().has_entry(name))
			{
				auto si = parser_->struct_table().get(name);
				return new ElsaType(si->get_expression());
			}

			throw ParsingException("Invalid struct name");
		}

		bool TypeChecker::valid_assignment(AssignmentExpression* assignment_expression)
		{
			return is_same_type(assignment_expression->get_left(), assignment_expression->get_right());
		}

		bool TypeChecker::valid_return_expression(Expression* expression)
		{
			if (is_of_type<ConditionalExpression>(expression))
			{
				return false;
			}

			if (is_of_type<LoopExpression>(expression))
			{
				return false;
			}

			if (is_of_type<ReturnExpression>(expression))
			{
				return false;
			}

			if (is_of_type<VariableDeclarationExpression>(expression))
			{
				return false;
			}

			return true;
		}

		bool TypeChecker::return_type_match(FuncDeclarationExpression* expression)
		{
			auto declared_return_type = expression->get_return_type();
			auto return_expressions = std::vector<Expression*>();

			for (const auto& exp : expression->get_body())
			{
				if (is_of_type<ReturnExpression>(exp.get()))
				{
					return_expressions.push_back(exp.get());
				}
			}

			if (declared_return_type->get_type() != ObjectType::Void && return_expressions.size() == 0)
				throw ParsingException("The function must return a value");

			for (const auto return_exp : return_expressions)
			{
				auto return_expression_type = get_expression_type(return_exp);
				if (!is_same_type(return_expression_type, declared_return_type))
					return false;
			}

			return true;
		}

		bool TypeChecker::is_boolean_operator(TokenType op)
		{
			switch (op)
			{
			case TokenType::GreaterThan:
			case TokenType::LessThan:
			case TokenType::GreaterThanEquals:
			case TokenType::LessThanEquals:
			case TokenType::DoubleEquals:
			case TokenType::NotEquals:
				return true;
			default:
				return false;
			}
		}

		template<typename TExpression>
		bool TypeChecker::is_of_type(Expression* exp)
		{
			return dynamic_cast<TExpression*>(exp) != nullptr;
		}
	}
}
