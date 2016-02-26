#include "enum_declaration_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> EnumDeclarationParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::Enum);

			auto enum_name = parser->current_token()->get_value();
			parser->consume(TokenType::Identifier);
			parser->consume(TokenType::LBracket);

			auto enum_dec_exp = std::make_unique<EnumDeclarationExpression>();
			enum_dec_exp->set_name(enum_name);

			auto enum_value = 0;
			while (parser->current_token()->get_type() != TokenType::RBracket)
			{
				auto member_name = parser->current_token()->get_value();
				parser->consume(TokenType::Identifier);

				if (parser->current_token()->get_type() != TokenType::Comma && parser->current_token()->get_type() != TokenType::RBracket)
				{
					parser->consume(TokenType::Equals);
					auto new_enum_value = parser->current_token()->get_value();
					parser->consume(TokenType::IntegerLiteral);
					enum_value = std::stoi(new_enum_value, nullptr);
				}

				enum_dec_exp->add_value(member_name, enum_value++);

				if(parser->current_token()->get_type() == TokenType::Comma)
					parser->consume(TokenType::Comma);
			}

			parser->consume(TokenType::RBracket);
			parser->consume(TokenType::Semicolon);

			parser->add_enum(enum_dec_exp.get());

			return std::move(enum_dec_exp);
		}
	}
}
