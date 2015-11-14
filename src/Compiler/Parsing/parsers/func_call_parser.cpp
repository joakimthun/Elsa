#include "func_call_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> FuncCallParser::parse(ElsaParser* parser)
		{
			auto func_name = parser->current_token()->get_value();

			if (!parser->function_table().has_entry(func_name))
				throw ParsingException("Can not call undefined functions");

			parser->consume(TokenType::Identifier);
			parser->consume(TokenType::LParen);

			auto call_exp = std::make_unique<FuncCallExpression>();
			call_exp->set_name(func_name);

			auto index = 0;
			auto fde = parser->function_table().get(func_name)->get_expression();
			auto& fde_args = fde->get_args();
			while (parser->current_token()->get_type() != TokenType::RParen)
			{
				if(index >= fde->get_num_args())
					throw ParsingException("To many arguments was passed to the function");

				auto passed_arg = parser->parse_expression();
				auto& declared_arg = fde_args[index];

				if (!parser->type_checker().is_same_type(passed_arg.get(), declared_arg.get()))
					throw ParsingException("The passed argument must be of the same type as the declared argument");

				call_exp->add_args_expression(std::move(passed_arg));

				if(parser->current_token()->get_type() != TokenType::RParen)
					parser->consume(TokenType::Comma);

				index++;
			}

			if(index != fde->get_num_args())
				throw ParsingException("To few arguments was passed to the function");

			parser->consume(TokenType::RParen);
			parser->consume(TokenType::Semicolon);

			return std::move(call_exp);
		}

	}
}

