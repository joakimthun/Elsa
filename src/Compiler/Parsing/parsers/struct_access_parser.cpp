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
					const auto type = get_parent_type(sa_exp.get());

					auto access_type = parser->type_checker().get_access_type(type, identifier);

					if (access_type->get_type() == ObjectType::Function)
					{
						auto call_exp = FuncCallParser::parse_member_call(parser, type->get_struct_declaration_expression()->get_member_function(identifier));
						sa_exp->add_expression(dynamic_cast<TypedExpression*>(call_exp.release()));
					}
					else
					{
						parser->consume(TokenType::Identifier);

						auto fa_exp = std::make_unique<FieldAccessExpression>(identifier);
						fa_exp->set_type(access_type);
						sa_exp->add_expression(fa_exp.release());
					}
				}

				if (parser->current_token()->get_type() == TokenType::Dot)
					parser->consume(TokenType::Dot);
				else
					return std::move(sa_exp);
			}

			return std::move(sa_exp);
		}

		const ElsaType* StructAccessParser::get_parent_type(StructAccessExpression* sa_exp)
		{
			if (sa_exp->get_expressions().size() > 0)
			{
				return sa_exp->get_expressions().back()->get_type();
			}

			return sa_exp->get_base()->get_type();
		}

	}
}
