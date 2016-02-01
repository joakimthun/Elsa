#include "type_cast_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> TypeCastParser::parse(ElsaParser* parser)
		{
			auto cast_exp = std::make_unique<TypeCastExpression>();
			cast_exp->set_dest_type(get_dest_type(parser));
			parser->consume();

			parser->consume(TokenType::LParen);
			cast_exp->set_expression(parser->parse_expression());
			parser->consume(TokenType::RParen);

			auto exp_type = std::unique_ptr<ElsaType>(parser->type_checker().get_expression_type(cast_exp->get_expression()));
			if (cast_exp->get_dest_type()->are_equal(exp_type.get()))
				throw ParsingException(L"Invalid cast: The expression is already of that type", parser->current_token());

			return std::move(cast_exp);
		}

		ElsaType* TypeCastParser::get_dest_type(ElsaParser* parser)
		{
			switch (parser->current_token()->get_type())
			{
			case TokenType::Int:
				return new ElsaType(ObjectType::Int);
			case TokenType::Char:
				return new ElsaType(ObjectType::Char);
			case TokenType::Float:
				return new ElsaType(ObjectType::Float);
			default:
				throw ParsingException(L"Cast: unsupported destination type", parser->current_token());
			}
		}

	}
}
