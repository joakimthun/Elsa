#include "variable_declaration_parser.h"

namespace elsa {
	namespace compiler {

		Expression* VariableDeclarationParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::Var);

			auto name = parser->current_token()->get_value();

			parser->consume(TokenType::Identifier);
			parser->consume(TokenType::Equals);

			auto expression = std::unique_ptr<Expression>(parser->parse_expression());
			auto expression_type = TypeChecker::get_expression_type(expression.get());

			parser->consume(TokenType::Semicolon);

			return new VariableDeclarationExpression(name, expression_type, expression.release());
		}

	}
}
