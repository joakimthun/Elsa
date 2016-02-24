#include "grouped_expression_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> GroupedExpressionParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::LParen);
			auto grp_exp = std::make_unique<GroupedExpression>();

			grp_exp->set_expression(parser->parse_expression());

			grp_exp->set_type(parser->type_checker().get_expression_type(grp_exp->get_expression()));

			parser->consume(TokenType::RParen);

			return std::move(grp_exp);
		}
	}
}
