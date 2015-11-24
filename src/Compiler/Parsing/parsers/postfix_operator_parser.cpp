#include "postfix_operator_parser.h"

namespace elsa {
	namespace compiler {

		PostfixOperatorParser::PostfixOperatorParser(Precedence precedence)
			:
			precedence_(precedence)
		{}

		std::unique_ptr<Expression> PostfixOperatorParser::parse(ElsaParser* parser, std::unique_ptr<Expression> left)
		{
			auto exp = std::make_unique<PostfixOperatorExpression>();
			exp->set_expression(std::move(left));
			exp->set_operator(parser->current_token()->get_type());

			// Consume the operator token
			parser->consume();

			exp->set_type(parser->type_checker().get_expression_type(exp->get_expression()));

			return std::move(exp);
		}

		int PostfixOperatorParser::precedence()
		{
			return static_cast<int>(precedence_);
		}

	}
}
