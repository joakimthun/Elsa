#include "anonymous_func_declaration_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> AnonymousFuncDeclarationParser::parse(ElsaParser* parser)
		{
			auto func_dec_exp = parse_signature(parser);

			auto parent_scope = parser->current_scope();
			parser->set_current_scope(func_dec_exp.get());

			auto variable_name = parser->current_token()->get_value();
			parser->consume(TokenType::Identifier);

			parser->consume(TokenType::Equals);

			parser->consume(TokenType::LParen);

			for (auto& arg : func_dec_exp->get_args())
			{
				arg->set_name(parser->current_token()->get_value());
				parser->consume(TokenType::Identifier);
				parser->current_scope()->add_arg(arg->get_name(), arg->get_type());
			}

			parser->consume(TokenType::RParen);

			parser->consume(TokenType::Equals);
			parser->consume(TokenType::GreaterThan);

			parser->consume(TokenType::LBracket);

			while (parser->current_token()->get_type() != TokenType::RBracket)
			{
				func_dec_exp->add_body_expression(parser->parse_expression());
			}

			if (!parser->type_checker().return_type_match(func_dec_exp.get()))
				throw ParsingException(L"Return type mismatch", parser->current_token());

			parser->set_current_scope(parent_scope);

			parser->consume(TokenType::RBracket);
			parser->consume(TokenType::Semicolon);

			auto type = std::unique_ptr<ElsaType>(parser->type_checker().get_expression_type(func_dec_exp.get()));
			parser->current_scope()->add_local(variable_name, *type);

			return std::make_unique<VariableDeclarationExpression>(variable_name, type.release(), std::move(func_dec_exp));
		}

		std::unique_ptr<FuncDeclarationExpression> AnonymousFuncDeclarationParser::parse_signature(ElsaParser* parser)
		{
			parser->consume(TokenType::Func);
			parser->consume(TokenType::LessThan);

			auto func_dec_exp = std::make_unique<FuncDeclarationExpression>();
			func_dec_exp->set_anonymous(true);
			auto name = StringUtil::create_random_string(20);
			func_dec_exp->set_name(name);

			auto ret_type = std::unique_ptr<ElsaType>(parser->type_checker().get_type_from_token(parser->current_token()));

			if (parser->current_token()->get_type() == TokenType::LSBracket)
			{
				auto array_struct = parser->struct_table().get(L"Array")->get_expression();
				auto array_type = array_struct->create_generic(std::move(ret_type), parser);

				parser->consume(TokenType::LSBracket);
				parser->consume(TokenType::RSBracket);

				func_dec_exp->set_return_type(new ElsaType(array_type));
			}
			else
			{
				func_dec_exp->set_return_type(ret_type.release());
			}

			if (parser->current_token()->get_type() == TokenType::Comma)
				parser->consume(TokenType::Comma);

			while (parser->current_token()->get_type() != TokenType::GreaterThan)
			{
				auto arg = std::make_unique<ArgumentExpression>();
				auto type = std::unique_ptr<ElsaType>(parser->type_checker().get_type_from_token(parser->current_token()));

				if (parser->current_token()->get_type() == TokenType::LSBracket)
				{
					auto array_struct = parser->struct_table().get(L"Array")->get_expression();
					auto array_type = array_struct->create_generic(std::move(type), parser);

					parser->consume(TokenType::LSBracket);
					parser->consume(TokenType::RSBracket);

					arg->set_type(new ElsaType(array_type));
				}
				else
				{
					arg->set_type(type.release());
				}

				func_dec_exp->add_args_expression(std::move(arg));

				if (parser->current_token()->get_type() != TokenType::GreaterThan)
					parser->consume(TokenType::Comma);
			}

			parser->consume(TokenType::GreaterThan);

			return func_dec_exp;
		}

	}
}