#include "type_checker.h"

#include "../parsing/elsa_parser.h"
#include "../parsing/helpers/func_parser_helper.h"

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
					throw ParsingException(L"Type mismatch", parser_->current_token());
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

				if (id->get_type() != nullptr)
					return new ElsaType(id->get_type());

				auto local = parser_->current_scope()->get_local(id->get_name());

				if (local == nullptr)
				{
					if (parser_->function_table().has_entry(id->get_name()))
					{
						return new ElsaType(parser_->function_table().get(id->get_name())->get_expression());
					}

					local = parser_->current_scope()->get_local_from_closure(id->get_name());
					if (local != nullptr)
					{
						id->set_from_closure(true);

						if (local->get_struct_expression() != nullptr)
						{
							return new ElsaType(local->get_struct_expression());
						}
						else
						{
							return new ElsaType(local->get_type());
						}
					}

					throw ParsingException(L"Unkown identifier '" + id->get_name() + L"'", parser_->current_token());
				}

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
			if (is_of_type<StructInitializerListExpression>(expression))
			{
				auto sile = static_cast<StructInitializerListExpression*>(expression);
				return new ElsaType(sile->get_create_struct_expression()->get_type()->get_struct_declaration_expression());
			}
			if (is_of_type<FieldAccessExpression>(expression))
			{
				auto fae = static_cast<FieldAccessExpression*>(expression);
				auto local = parser_->current_scope()->get_local(fae->get_name());

				if (local == nullptr)
					throw ParsingException(L"Invalid field name", parser_->current_token());

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

				const ElsaType* current = parser_->current_struct_type();
				if(sae->get_base() != nullptr)
					current = sae->get_base()->get_type();

				std::unique_ptr<ElsaType> type;

				for (const auto& field_expression : sae->get_expressions())
				{
					if (field_expression->get_expression_type() == ExpressionType::ArrayAccess)
					{
						auto aae = static_cast<ArrayAccessExpression*>(field_expression.get());
						type.reset(new ElsaType(aae->get_identifier_expression()->get_type()));
					
						if (aae->get_identifier_expression()->get_type()->get_type() == ObjectType::GCOPtr)
							current = aae->get_identifier_expression()->get_type();
					}
					else if (field_expression->get_expression_type() == ExpressionType::Identifier)
					{
						return new ElsaType(field_expression->get_type());
					}
					else
					{
						type.reset(get_access_type(current, field_expression->get_name()));

						if (field_expression->get_type()->get_type() == ObjectType::GCOPtr)
							current = field_expression->get_type();
					}
				}

				if (type->get_type() == ObjectType::Function)
					return new ElsaType(type->get_func_declaration_expression()->get_return_type());

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
				return get_expression_type(re->get_expression());
			}
			if (is_of_type<ArrayDeclarationExpression>(expression))
			{
				auto ade = static_cast<ArrayDeclarationExpression*>(expression);
				return new ElsaType(ade->get_type(), true);
			}
			if (is_of_type<ArrayAccessExpression>(expression))
			{
				auto aae = static_cast<ArrayAccessExpression*>(expression);
				return new ElsaType(aae->get_identifier_expression()->get_type(), true);
			}
			if (is_of_type<ArrayInitializerListExpression>(expression))
			{
				auto ade = static_cast<ArrayInitializerListExpression*>(expression);
				return new ElsaType(ade->get_type(), true);
			}
			if (is_of_type<StructDeclarationExpression>(expression))
			{
				auto sde = static_cast<StructDeclarationExpression*>(expression);
				return new ElsaType(sde);
			}
			if (is_of_type<StringLiteralExpression>(expression))
			{
				auto sle = static_cast<StringLiteralExpression*>(expression);
				auto string_struct = parser_->struct_table().get(L"String");
				return new ElsaType(string_struct->get_expression());
			}
			if (is_of_type<TypeCastExpression>(expression))
			{
				auto tce = static_cast<TypeCastExpression*>(expression);
				return new ElsaType(tce->get_dest_type());
			}
			if (is_of_type<FuncDeclarationExpression>(expression))
			{
				auto fde = static_cast<FuncDeclarationExpression*>(expression);
				return new ElsaType(fde);
			}
			if (is_of_type<GroupedExpression>(expression))
			{
				auto grp = static_cast<GroupedExpression*>(expression);
				return new ElsaType(grp->get_type());
			}
			if (is_of_type<EnumValueExpression>(expression))
			{
				auto eve = static_cast<EnumValueExpression*>(expression);
				return new ElsaType(eve->get_type());
			}
			if (is_of_type<PostfixOperatorExpression>(expression))
			{
				auto poe = static_cast<PostfixOperatorExpression*>(expression);
				return new ElsaType(poe->get_type());
			}

			throw ParsingException(L"TypeChecker::get_expression_type -> Unkown expression type.", parser_->current_token());
		}

		ElsaType* TypeChecker::get_type_from_token(Token* token)
		{
			auto token_type = token->get_type();
			ElsaType* type = nullptr;
			switch (token_type)
			{
			case TokenType::Void: {
				type = new ElsaType(ObjectType::Void);
				break;
			}
			case TokenType::Int: {
				type = new ElsaType(ObjectType::Int);
				break;
			}
			case TokenType::Float: {
				type = new ElsaType(ObjectType::Float);
				break;
			}
			case TokenType::Char: {
				type = new ElsaType(ObjectType::Char);
				break;
			}
			case TokenType::Bool: {
				type = new ElsaType(ObjectType::Bool);
				break;
			}
			case TokenType::Byte: {
				type = new ElsaType(ObjectType::Byte);
				break;
			}
			case TokenType::IntegerLiteral: {
				type = new ElsaType(ObjectType::Int);
				break;
			}
			case TokenType::FloatLiteral: {
				type = new ElsaType(ObjectType::Float);
				break;
			}
			case TokenType::CharLiteral: {
				type = new ElsaType(ObjectType::Char);
				break;
			}
			case TokenType::BoolLiteral: {
				type = new ElsaType(ObjectType::Bool);
				break;
			}
			case TokenType::Object: {
				type = new ElsaType(ObjectType::Object);
				break;
			}
			case TokenType::Identifier: {
				type = get_struct_or_enum_type(token->get_value());
				break;
			}
			case TokenType::Func: {
				return get_func_type();
			}
			default:
				throw ParsingException(L"Expected a type, found: '" + Token::to_string(parser_->current_token()->get_type()) + L"'", parser_->current_token());
			}

			parser_->consume();
			return type;
		}

		void TypeChecker::assert_is_same_type(ObjectType t1, ObjectType t2)
		{
			if (t1 != t2)	
				throw ParsingException(L"Type mismatch", parser_->current_token());
		}

		bool TypeChecker::is_same_type(Expression* first, Expression* second)
		{
			auto left = std::unique_ptr<ElsaType>(get_expression_type(first));

			if (left->get_type() == ObjectType::GCOPtr && left->get_struct_declaration_expression()->is_generic_type())
				left.reset(new ElsaType(left->get_struct_declaration_expression()->get_generic_type()));

			auto right = std::unique_ptr<ElsaType>(get_expression_type(second));

			if (right->get_type() == ObjectType::GCOPtr && right->get_struct_declaration_expression()->is_generic_type())
				right.reset(new ElsaType(right->get_struct_declaration_expression()->get_generic_type()));

			return left->are_equal(right.get());
		}

		ElsaType* TypeChecker::get_access_type(const ElsaType* type, const std::wstring& name, bool throw_invalid_exception)
		{
			if (type->get_type() == ObjectType::Function)
				return new ElsaType(type->get_func_declaration_expression()->get_return_type());

			auto struct_expression = type->get_struct_declaration_expression();
			if(struct_expression == nullptr)
				throw ParsingException(L"The StructDeclarationExpression can not be a nullptr", parser_->current_token());

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

			if(throw_invalid_exception)
				throw ParsingException(L"'" + struct_expression->get_name() + L"' has no field or function with the name '" + name + L"'", parser_->current_token());

			return nullptr;
		}

		ElsaType* TypeChecker::get_struct_or_enum_type(const std::wstring& name)
		{
			if (parser_->struct_table().has_entry(name))
			{
				auto si = parser_->struct_table().get(name);
				return new ElsaType(si->get_expression());
			}

			auto enum_exp = parser_->get_enum(name);
			if (enum_exp != nullptr)
				return new ElsaType(enum_exp);
			
			throw ParsingException(L"Invalid struct or enum name", parser_->current_token());
		}

		ElsaType* TypeChecker::get_func_type()
		{
			// TODO: Reuse functions with the same signature?
			function_signatures_.push_back(FuncParserHelper::parse_signature(parser_, true, nullptr));

			auto fde = function_signatures_.back().get();
			fde->set_num_args(fde->get_args().size());

			return new ElsaType(fde);
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
			auto return_expressions = expression->get_return_expressions();

			auto non_nested_return_expressions = std::vector<Expression*>();

			for (const auto& exp : expression->get_body())
			{
				if (is_of_type<ReturnExpression>(exp.get()))
				{
					non_nested_return_expressions.push_back(exp.get());
				}
			}

			if (declared_return_type->get_type() != ObjectType::Void && return_expressions.expressions.size() == 0)
				throw ParsingException(L"The function '" + expression->get_name() + L"' must return a value", parser_->current_token());

			if (declared_return_type->get_type() != ObjectType::Void && non_nested_return_expressions.size() == 0 && !return_expressions.if_else_with_return)
				throw ParsingException(L"All paths of the function '" + expression->get_name() + L"' must return a value", parser_->current_token());

			for (const auto return_exp : return_expressions.expressions)
			{
				auto return_expression_type = get_expression_type(return_exp);
				if (!return_expression_type->are_equal(declared_return_type))
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

		bool TypeChecker::is_assignable(Expression* expression)
		{
			return is_of_type<IdentifierExpression>(expression) ||
				is_of_type<StructAccessExpression>(expression) ||
				is_of_type<ArrayAccessExpression>(expression);
		}

		template<typename TExpression>
		bool TypeChecker::is_of_type(Expression* exp)
		{
			return dynamic_cast<TExpression*>(exp) != nullptr;
		}
	}
}
