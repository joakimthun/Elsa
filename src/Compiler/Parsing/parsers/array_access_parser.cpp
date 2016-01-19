#include "array_access_parser.h"

#include "struct_access_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> ArrayAccessParser::parse(ElsaParser* parser)
		{
			return parse_static(parser);
		}

		std::unique_ptr<Expression> ArrayAccessParser::parse_static(ElsaParser* parser)
		{
			auto arr_exp = std::make_unique<ArrayAccessExpression>();

			auto identifier = parser->current_token()->get_value();
			parser->consume(TokenType::Identifier);

			auto id_exp = std::make_unique<IdentifierExpression>(identifier);

			std::unique_ptr<ElsaType> array_type;
			if (parser->current_type() != nullptr)
			{
				array_type = std::unique_ptr<ElsaType>(parser->type_checker().get_access_type(parser->current_type(), identifier));
			}
			else
			{
				array_type = std::unique_ptr<ElsaType>(parser->type_checker().get_expression_type(id_exp.get()));
			}

			if (array_type->get_struct_declaration_expression() == nullptr || array_type->get_struct_declaration_expression()->get_name(true) != L"Array")
				throw ParsingException(L"Only arrays can be accessed by index.", parser->current_token());

			id_exp->set_type(new ElsaType(array_type->get_struct_declaration_expression()->get_generic_type()));

			arr_exp->set_identifier_expression(std::move(id_exp));

			parser->consume(TokenType::LSBracket);

			auto index_expression = parser->parse_expression();
			auto index_expression_type = std::unique_ptr<ElsaType>(parser->type_checker().get_expression_type(index_expression.get()));

			if (index_expression_type->get_type() != ObjectType::Int)
				throw ParsingException(L"Only integers are supported when accessing array elements", parser->current_token());

			arr_exp->set_index_expression(std::move(index_expression));

			parser->consume(TokenType::RSBracket);

			if (parser->current_token()->get_type() == TokenType::Dot)
			{
				if (arr_exp->get_identifier_expression()->get_type()->get_type() != ObjectType::GCOPtr)
					throw ParsingException(L"Only struct fields and functions can be accessed by the '.' operator", parser->current_token());

				parser->consume(TokenType::Dot);
				parser->set_current_type(arr_exp->get_identifier_expression()->get_type());

				auto sae = StructAccessParser::parse_static(parser);
				arr_exp->set_struct_access_expression(dynamic_cast<StructAccessExpression*>(sae.release()));

				parser->set_current_type(nullptr);
			}

			return std::move(arr_exp);
		}

	}
}
