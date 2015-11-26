#include "array_declaration_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> ArrayDeclarationParser::parse(ElsaParser* parser)
		{
			auto arr_exp = std::make_unique<ArrayDeclarationExpression>();
			arr_exp->set_type(parser->type_checker().get_type_from_token(parser->current_token()));

			parser->consume();
			parser->consume(TokenType::LSBracket);
			parser->consume(TokenType::RSBracket);

			return std::move(arr_exp);
		}

	}
}
