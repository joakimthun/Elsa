#include "struct_access_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> StructAccessParser::parse(ElsaParser* parser)
		{
			return parse_static(parser);
		}

		std::unique_ptr<Expression> StructAccessParser::parse_static(ElsaParser* parser)
		{
			auto sa_exp = std::make_unique<StructAccessExpression>();

			while (parser->current_token()->get_type() == TokenType::Identifier)
			{
				auto identifier = parser->current_token()->get_value();

				if (sa_exp->get_base() == nullptr && parser->current_type() == nullptr)
				{
					// Local
					auto id_exp = std::make_unique<IdentifierExpression>(identifier);
					parser->consume(TokenType::Identifier);

					id_exp->set_type(parser->type_checker().get_expression_type(id_exp.get()));

					parser->set_current_type(id_exp->get_type());

					sa_exp->set_base(std::move(id_exp));
				}
				else
				{
					// Field or function
					const auto type = get_parent_type(sa_exp.get(), parser);
					parser->set_current_type(type);

					auto access_type = parser->type_checker().get_access_type(type, identifier);

					if (access_type->get_type() == ObjectType::Function)
					{
						auto call_exp = FuncCallParser::parse_member_call(parser, type->get_struct_declaration_expression()->get_member_function(identifier));
						sa_exp->add_expression(dynamic_cast<TypedExpression*>(call_exp.release()));
					}
					else if (parser->peek_token()->get_type() == TokenType::LSBracket)
					{
						auto array_access_exp = parser->parse_expression();
						sa_exp->add_expression(dynamic_cast<TypedExpression*>(array_access_exp.release()));
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
				{
					parser->set_current_type(nullptr);
					return std::move(sa_exp);
				}
			}

			parser->set_current_type(nullptr);
			return std::move(sa_exp);
		}

		const ElsaType* StructAccessParser::get_parent_type(StructAccessExpression* sa_exp, ElsaParser* parser)
		{
			if (sa_exp->get_expressions().size() > 0)
			{
				return sa_exp->get_expressions().back()->get_type();
			}

			if (sa_exp->get_base() == nullptr && parser->current_type() != nullptr)
				return parser->current_type();

			return sa_exp->get_base()->get_type();
		}

	}
}
