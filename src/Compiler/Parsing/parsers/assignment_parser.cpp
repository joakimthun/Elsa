#include "assignment_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> AssignmentParser::parse(ElsaParser* parser, std::unique_ptr<Expression> left)
		{
			parser->consume(TokenType::Equals);

			auto exp = std::make_unique<AssignmentExpression>();

			exp->set_left(std::move(left));

			if (!parser->type_checker().is_of_type<IdentifierExpression>(exp->get_left()) && !parser->type_checker().is_of_type<StructAccessExpression>(exp->get_left()))
				throw ParsingException("Values can only be assigned to local variables");

			exp->set_right(std::move(parser->parse_expression(precedence())));

			parser->consume(TokenType::Semicolon);

			return std::move(exp);
		}

		int AssignmentParser::precedence()
		{
			return Precedence::Assignment;
		}

	}
}
