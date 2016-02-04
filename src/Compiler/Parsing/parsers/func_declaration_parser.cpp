#include "func_declaration_parser.h"

#include "../helpers/func_parser_helper.h"

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

			auto func_dec_exp = FuncParserHelper::parse_signature(parser, false, parent);
			func_dec_exp->set_is_native(native_function);

			parser->push_new_scope(func_dec_exp.get());

			if (parent != nullptr)
			{
				// If we are parsing a member function we pass a reference to the struct instance as the first argument
				auto arg = std::make_unique<ArgumentExpression>(ArgumentType::InstRef);
				arg->set_type(parser->type_checker().get_expression_type(parent));
				arg->set_name(L"this");
				parser->current_scope()->add_arg(arg->get_name(), arg->get_type());
				func_dec_exp->add_args_expression_to_front(std::move(arg));
			}

			func_dec_exp->set_num_args(0);
			for (auto& arg : func_dec_exp->get_args())
			{
				parser->current_scope()->add_arg(arg->get_name(), arg->get_type());
			}

			if (parent == nullptr)
				parser->function_table().add_function(func_dec_exp.get());

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

			parser->pop_current_scope();

			parser->consume(TokenType::RBracket);

			return std::move(func_dec_exp);
		}

	}
}