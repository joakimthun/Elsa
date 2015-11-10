#include "struct_declaration_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> StructDeclarationParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::Struct);

			auto struct_exp = std::make_unique<StructDeclarationExpression>();

			auto name = parser->current_token()->get_value();

			struct_exp->set_name(name);

			parser->consume(TokenType::Identifier);
			parser->consume(TokenType::LBracket);

			while (parser->current_token()->get_type() != TokenType::RBracket)
			{
				struct_exp->add_field_expression(parse_field_expression(parser));
			}

			parser->consume(TokenType::RBracket);
			parser->consume(TokenType::Semicolon);

			return std::move(struct_exp);
		}

		std::unique_ptr<FieldExpression> StructDeclarationParser::parse_field_expression(ElsaParser* parser)
		{
			auto field_type = TypeChecker::get_type_from_token(parser->current_token()->get_type());

			parser->consume();

			auto field_expression = std::make_unique<FieldExpression>();

			field_expression->set_type(field_type);

			auto field_name = parser->current_token()->get_value();
			parser->consume(TokenType::Identifier);

			field_expression->set_name(field_name);

			parser->consume(TokenType::Semicolon);

			return std::move(field_expression);
		}

	}
}