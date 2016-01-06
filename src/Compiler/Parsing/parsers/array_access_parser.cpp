#include "array_access_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> ArrayAccessParser::parse(ElsaParser* parser)
		{
			auto arr_exp = std::make_unique<ArrayAccessExpression>();

			auto identifier = parser->current_token()->get_value();
			parser->consume(TokenType::Identifier);

			auto id_exp = std::make_unique<IdentifierExpression>(identifier);
			id_exp->set_type(parser->type_checker().get_expression_type(id_exp.get()));

			arr_exp->set_identifier_expression(std::move(id_exp));

			parser->consume(TokenType::LSBracket);

			auto index_expression = parser->parse_expression();
			auto index_expression_type = std::unique_ptr<ElsaType>(parser->type_checker().get_expression_type(index_expression.get()));

			if (index_expression_type->get_type() != ObjectType::Int)
				throw ParsingException("Only integers are supported when accessing array elements");

			arr_exp->set_index_expression(std::move(index_expression));

			parser->consume(TokenType::RSBracket);

			return std::move(arr_exp);
		}

	}
}
