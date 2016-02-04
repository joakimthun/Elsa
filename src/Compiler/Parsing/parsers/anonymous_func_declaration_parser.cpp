#include "anonymous_func_declaration_parser.h"

#include "../helpers/func_parser_helper.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> AnonymousFuncDeclarationParser::parse(ElsaParser* parser)
		{
			auto func_dec_exp = FuncParserHelper::parse_signature(parser, true, nullptr);

			auto parent_scope = parser->current_scope();
			parser->push_new_scope(func_dec_exp.get());

			for (auto& arg : func_dec_exp->get_args())
			{
				parser->current_scope()->add_arg(arg->get_name(), arg->get_type());
			}

			parser->consume(TokenType::Equals);
			parser->consume(TokenType::GreaterThan);
			parser->consume(TokenType::LBracket);

			while (parser->current_token()->get_type() != TokenType::RBracket)
			{
				func_dec_exp->add_body_expression(parser->parse_expression());
			}

			if (!parser->type_checker().return_type_match(func_dec_exp.get()))
				throw ParsingException(L"Return type mismatch", parser->current_token());

			parser->push_new_scope(parent_scope);

			parser->consume(TokenType::RBracket);

			// If the function is passed directly no semi colon should be specified
			if(parser->current_token()->get_type() == TokenType::Semicolon)
				parser->consume(TokenType::Semicolon);

			return std::move(func_dec_exp);
		}

	}
}