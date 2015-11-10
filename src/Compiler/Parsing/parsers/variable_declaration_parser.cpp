#include "variable_declaration_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> VariableDeclarationParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::Var);

			auto name = parser->current_token()->get_value();

			parser->consume(TokenType::Identifier);
			parser->consume(TokenType::Equals);

			auto expression = std::unique_ptr<Expression>(parser->parse_expression());
			auto expression_type = TypeChecker::get_expression_type(expression.get());

			parser->consume(TokenType::Semicolon);

			return std::make_unique<VariableDeclarationExpression>(name, expression_type, std::move(expression));
		}

	}
}
