#include "variable_declaration_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> VariableDeclarationParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::Var);

			auto name = parser->current_token()->get_value();

			if (parser->current_scope()->has_local(name))
				throw ParsingException("A local variable with the same name has already been declared");

			parser->consume(TokenType::Identifier);
			parser->consume(TokenType::Equals);

			auto expression = std::unique_ptr<Expression>(parser->parse_expression());
			auto expression_type = parser->type_checker().get_expression_type(expression.get());

			parser->current_scope()->add_local(name, *expression_type);

			parser->consume(TokenType::Semicolon);

			return std::make_unique<VariableDeclarationExpression>(name, expression_type, std::move(expression));
		}

	}
}
