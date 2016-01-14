#include "func_declaration_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> FuncDeclarationParser::parse(ElsaParser* parser)
		{
			bool native_function = false;
			if (parser->current_token()->get_type() == TokenType::Native)
			{
				native_function = true;
				parser->consume(TokenType::Native);
			}

			parser->consume(TokenType::Func);

			auto func_dec_exp = std::make_unique<FuncDeclarationExpression>(native_function);

			func_dec_exp->set_return_type(parser->type_checker().get_type_from_token(parser->current_token()));
			parser->consume();

			auto name = parser->current_token()->get_value();
			parser->consume(TokenType::Identifier);

			if (parser->function_table().has_entry(name))
				throw ParsingException(L"A function with the same name has already been declared", parser->current_token());

			func_dec_exp->set_name(name);

			parser->function_table().add_function(func_dec_exp.get());

			parser->consume(TokenType::LParen);

			parser->set_current_scope(func_dec_exp.get());

			while (parser->current_token()->get_type() != TokenType::RParen)
			{
				auto arg = std::make_unique<ArgumentExpression>();
				arg->set_type(parser->type_checker().get_type_from_token(parser->current_token()));
				parser->consume();

				
				arg->set_name(parser->current_token()->get_value());
				parser->consume(TokenType::Identifier);

				parser->current_scope()->add_arg(arg->get_name(), arg->get_type());

				func_dec_exp->add_args_expression(std::move(arg));

				if(parser->current_token()->get_type() != TokenType::RParen)
					parser->consume(TokenType::Comma);
			}

			parser->consume(TokenType::RParen);

			if (native_function)
			{
				parser->consume(TokenType::Semicolon);
				return std::move(func_dec_exp);
			}

			parser->consume(TokenType::LBracket);

			while (parser->current_token()->get_type() != TokenType::RBracket)
			{
				func_dec_exp->add_body_expression(parser->parse_expression());
			}

			parser->reset_current_scope();

			if (!parser->type_checker().return_type_match(func_dec_exp.get()))
				throw ParsingException(L"Return type mismatch", parser->current_token());

			parser->consume(TokenType::RBracket);

			return std::move(func_dec_exp);
		}

	}
}