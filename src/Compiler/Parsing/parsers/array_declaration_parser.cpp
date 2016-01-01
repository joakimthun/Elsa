#include "array_declaration_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> ArrayDeclarationParser::parse(ElsaParser* parser)
		{
			auto arr_exp = std::make_unique<ArrayDeclarationExpression>();

			auto type = parser->type_checker().get_type_from_token(parser->current_token());
			type->set_is_array(true);

			arr_exp->set_type(type);

			parser->consume();
			parser->consume(TokenType::LSBracket);
			parser->consume(TokenType::RSBracket);

			return std::move(arr_exp);
		}

	}
}
