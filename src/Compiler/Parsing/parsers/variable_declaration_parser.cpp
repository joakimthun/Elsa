#include "variable_declaration_parser.h"

namespace elsa {
	namespace compiler {

		Expression* VariableDeclarationParser::parse(ElsaParser* parser, Token* token)
		{
			parser->consume(TokenType::Var);

			auto name = parser->current_token()->get_value();

			parser->consume(TokenType::Identifier);
			parser->consume(TokenType::Equals);

			auto expression = parser->parse_expression();

			parser->consume(TokenType::Semicolon);

			return new VariableDeclarationExpression(name, L"int", expression);
		}

	}
}
