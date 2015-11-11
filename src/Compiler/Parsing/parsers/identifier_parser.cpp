#include "identifier_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> IdentifierParser::parse(ElsaParser* parser)
		{
			auto identifier = parser->current_token()->get_value();
			parser->consume(TokenType::Identifier);

			auto id_exp = std::make_unique<IdentifierExpression>(identifier);
			auto id_type = parser->type_checker().get_expression_type(id_exp.get());
			id_exp->set_type(id_type);

			return std::move(id_exp);
		}

	}
}
