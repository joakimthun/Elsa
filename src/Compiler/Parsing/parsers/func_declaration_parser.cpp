#include "func_declaration_parser.h"

namespace elsa {
	namespace compiler {

		Expression* FuncDeclarationParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::Func);

			auto func_dec_exp = std::make_unique<FuncDeclarationExpression>();

			func_dec_exp->set_return_type(TypeChecker::get_type_from_token(parser->current_token()->get_type()));
			parser->consume();

			func_dec_exp->set_name(parser->current_token()->get_value());
			parser->consume(TokenType::Identifier);

			parser->consume(TokenType::LParen);

			// Handle Args

			parser->consume(TokenType::RParen);

			parser->consume(TokenType::LBracket);

			while (parser->current_token()->get_type() != TokenType::RBracket)
			{
				func_dec_exp->add_expression(parser->parse_expression());
			}

			parser->consume(TokenType::RBracket);

			return func_dec_exp.release();
		}

	}
}