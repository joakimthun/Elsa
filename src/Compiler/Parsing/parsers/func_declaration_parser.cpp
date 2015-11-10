#include "func_declaration_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> FuncDeclarationParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::Func);

			auto func_dec_exp = std::make_unique<FuncDeclarationExpression>();

			func_dec_exp->set_return_type(TypeChecker::get_type_from_token(parser->current_token()->get_type()));
			parser->consume();

			auto name = parser->current_token()->get_value();
			parser->consume(TokenType::Identifier);

			if (parser->function_table().has_entry(name))
				throw ParsingException("A function with the same name has already been declared");

			parser->function_table().add_function(name, parser);
			parser->current_function()->locals().reset_num_locals_and_num_args();

			func_dec_exp->set_name(name);

			parser->consume(TokenType::LParen);

			while (parser->current_token()->get_type() != TokenType::RParen)
			{
				auto arg = std::make_unique<ArgumentExpression>();
				arg->set_type(TypeChecker::get_type_from_token(parser->current_token()->get_type()));
				parser->consume();

				arg->set_name(parser->current_token()->get_value());
				parser->consume(TokenType::Identifier);

				func_dec_exp->add_args_expression(std::move(arg));
				parser->current_function()->locals().increment_num_args();

				if(parser->current_token()->get_type() != TokenType::RParen)
					parser->consume(TokenType::Comma);
			}

			parser->consume(TokenType::RParen);

			parser->consume(TokenType::LBracket);

			parser->current_function()->locals().push_new_scope();

			while (parser->current_token()->get_type() != TokenType::RBracket)
			{
				func_dec_exp->add_body_expression(parser->parse_expression());
			}

			parser->current_function()->locals().pop_current_scope();

			parser->consume(TokenType::RBracket);

			return std::move(func_dec_exp);
		}

	}
}