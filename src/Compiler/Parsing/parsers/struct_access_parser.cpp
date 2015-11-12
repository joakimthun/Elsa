#include "struct_access_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> StructAccessParser::parse(ElsaParser* parser)
		{
			auto sa_exp = std::make_unique<StructAccessExpression>();

			while (parser->current_token()->get_type() == TokenType::Identifier)
			{
				auto identifier = parser->current_token()->get_value();

				if (sa_exp->get_base() == nullptr)
				{
					// Local
					auto id_exp = std::make_unique<IdentifierExpression>(identifier);
					parser->consume(TokenType::Identifier);

					id_exp->set_type(parser->type_checker().get_expression_type(id_exp.get()));
					sa_exp->set_base(std::move(id_exp));
				}
				else
				{
					// Field or function
					auto fa_exp = std::make_unique<FieldAccessExpression>(identifier);
					parser->consume(TokenType::Identifier);

					const auto* type = sa_exp->get_expressions().size() > 0 ?
						sa_exp->get_expressions().back()->get_type() :
						sa_exp->get_base()->get_type();

					fa_exp->set_type(parser->type_checker().get_field_type(type->get_struct_declaration_expression(), fa_exp.get()));
					sa_exp->add_expression(std::move(fa_exp));
				}

				if (parser->current_token()->get_type() == TokenType::Dot)
					parser->consume(TokenType::Dot);
				else
					return std::move(sa_exp);
			}

			return std::move(sa_exp);
		}

	}
}
