#include "func_parser_helper.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<FuncDeclarationExpression> FuncParserHelper::parse_signature(ElsaParser* parser, bool anonymous, StructDeclarationExpression* parent)
		{
			parser->consume(TokenType::Func);

			auto func_dec_exp = std::make_unique<FuncDeclarationExpression>();

			if (anonymous)
			{
				func_dec_exp->set_anonymous(true);
				auto name = StringUtil::create_random_string(20);
				func_dec_exp->set_name(name);
			}
			else
			{
				auto name = parser->current_token()->get_value();
				parser->consume(TokenType::Identifier);

				if (parent != nullptr)
				{
					if (parent->has_function(name))
						throw ParsingException(L"A member function with the name '" + name + L"' has already been declared", parser->current_token());
				}
				else
				{
					if (parser->function_table().has_entry(name))
						throw ParsingException(L"A function with the same name has already been declared", parser->current_token());
				}

				func_dec_exp->set_name(name);
			}

			if (parser->current_token()->get_type() == TokenType::LParen)
			{
				parser->consume(TokenType::LParen);

				while (parser->current_token()->get_type() != TokenType::RParen)
				{
					auto arg = std::make_unique<ArgumentExpression>();
					auto type = std::unique_ptr<ElsaType>(parser->type_checker().get_type_from_token(parser->current_token()));

					if (parser->current_token()->get_type() == TokenType::LSBracket)
					{
						auto array_struct = parser->struct_table().get(L"Array")->get_expression();
						auto array_type = array_struct->create_generic(std::move(type), parser);

						parser->consume(TokenType::LSBracket);
						parser->consume(TokenType::RSBracket);

						arg->set_type(new ElsaType(array_type));
					}
					else
					{
						arg->set_type(type.release());
					}

					arg->set_name(parser->current_token()->get_value());
					parser->consume(TokenType::Identifier);

					for (const auto& declared_arg : func_dec_exp->get_args())
					{
						if(arg->get_name() == declared_arg->get_name())
							throw ParsingException(L"An argument with the name '" + arg->get_name() + L"' has already been declared for the function '" + func_dec_exp->get_name() + L"'", parser->current_token());
					}

					func_dec_exp->add_args_expression(std::move(arg));

					if (parser->current_token()->get_type() != TokenType::RParen)
						parser->consume(TokenType::Comma);
				}

				parser->consume(TokenType::RParen);
			}

			if (parser->current_token()->get_type() == TokenType::Colon)
			{
				parser->consume(TokenType::Colon);
				auto ret_type = std::unique_ptr<ElsaType>(parser->type_checker().get_type_from_token(parser->current_token()));

				if (parser->current_token()->get_type() == TokenType::LSBracket)
				{
					auto array_struct = parser->struct_table().get(L"Array")->get_expression();
					auto array_type = array_struct->create_generic(std::move(ret_type), parser);

					parser->consume(TokenType::LSBracket);
					parser->consume(TokenType::RSBracket);

					func_dec_exp->set_return_type(new ElsaType(array_type));
				}
				else
				{
					func_dec_exp->set_return_type(ret_type.release());
				}
			}
			else
			{
				func_dec_exp->set_return_type(new ElsaType(ObjectType::Void));
			}

			return func_dec_exp;
		}

	}
}