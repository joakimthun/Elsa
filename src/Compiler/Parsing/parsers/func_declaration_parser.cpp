#include "func_declaration_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> FuncDeclarationParser::parse(ElsaParser* parser)
		{
			return parse_internal(parser, nullptr);
		}

		std::unique_ptr<Expression> FuncDeclarationParser::parse_member(ElsaParser* parser, StructDeclarationExpression* parent)
		{
			return parse_internal(parser, parent);
		}


		std::unique_ptr<Expression> FuncDeclarationParser::parse_internal(ElsaParser* parser, StructDeclarationExpression* parent)
		{
			bool native_function = false;
			if (parser->current_token()->get_type() == TokenType::Native)
			{
				native_function = true;
				parser->consume(TokenType::Native);
			}

			parser->consume(TokenType::Func);

			auto func_dec_exp = std::make_unique<FuncDeclarationExpression>(native_function);

			// Local 0 is only used by the compiler to store random data e.g. when populating arrays from array initializer lists so the type does not matter here.
			auto local_0_type = ElsaType(ObjectType::Object);
			func_dec_exp->add_local(L"0", local_0_type);

			auto ret_type = std::unique_ptr<ElsaType>(parser->type_checker().get_type_from_token(parser->current_token()));
			parser->consume();

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

			auto name = parser->current_token()->get_value();
			parser->consume(TokenType::Identifier);

			if (parent != nullptr)
			{
				if(parent->has_function(name))
					throw ParsingException(L"A member function with the name '" + name + L"' has already been declared", parser->current_token());
			}
			else
			{
				if (parser->function_table().has_entry(name))
					throw ParsingException(L"A function with the same name has already been declared", parser->current_token());
			}

			func_dec_exp->set_name(name);

			if(parent == nullptr)
				parser->function_table().add_function(func_dec_exp.get());

			parser->consume(TokenType::LParen);

			parser->set_current_scope(func_dec_exp.get());

			if (parent != nullptr)
			{
				// If we are parsing a member function we pass a reference to the struct instance as the first argument
				auto arg = std::make_unique<ArgumentExpression>(ArgumentType::InstRef);
				arg->set_type(parser->type_checker().get_expression_type(parent));
				arg->set_name(L"this");
				parser->current_scope()->add_arg(arg->get_name(), arg->get_type());
				func_dec_exp->add_args_expression(std::move(arg));
			}

			while (parser->current_token()->get_type() != TokenType::RParen)
			{
				auto arg = std::make_unique<ArgumentExpression>();
				auto type = std::unique_ptr<ElsaType>(parser->type_checker().get_type_from_token(parser->current_token()));
				parser->consume();

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

				parser->current_scope()->add_arg(arg->get_name(), arg->get_type());

				func_dec_exp->add_args_expression(std::move(arg));

				if (parser->current_token()->get_type() != TokenType::RParen)
					parser->consume(TokenType::Comma);
			}

			parser->consume(TokenType::RParen);

			if (native_function)
			{
				parser->consume(TokenType::Semicolon);
				return std::move(func_dec_exp);
			}

			parser->consume(TokenType::LBracket);

			while (parser->current_token()->get_type() != TokenType::RBracket)
			{
				func_dec_exp->add_body_expression(parser->parse_expression());
			}

			if (!parser->type_checker().return_type_match(func_dec_exp.get()))
				throw ParsingException(L"Return type mismatch", parser->current_token());

			parser->reset_current_scope();

			parser->consume(TokenType::RBracket);

			return std::move(func_dec_exp);
		}

	}
}