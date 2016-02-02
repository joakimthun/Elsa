#include "elsa_parser.h"

namespace elsa {
	namespace compiler {

		ElsaParser::ElsaParser(Lexer* lexer, bool load_default_imports)
			:
			parent_(nullptr),
			lexer_(std::unique_ptr<Lexer>(lexer)),
			current_scope_(nullptr),
			type_checker_(this),
			program_(std::make_unique<Program>()),
			current_type_(nullptr),
			current_struct_(nullptr)
		{
			initialize_grammar();
			next_token();
			Builtin::init(&struct_table_);

			if(load_default_imports)
				initialize_default_imports();
		}

		std::unique_ptr<Program> ElsaParser::parse()
		{
			while (current_token_->get_type() != TokenType::END)
			{
				program_->add_statement(parse_statement());
			}

			return std::move(program_);
		}

		std::unique_ptr<Expression> ElsaParser::parse_statement()
		{
			while(current_token_->get_type() == TokenType::Import)
				parse_import_statement();

			auto parser = get_statement_parser(current_token_->get_type());

			if (parser == nullptr)
				throw ParsingException(L"Invalid token", current_token_.get());

			return parser->parse(this);
		}

		std::unique_ptr<Expression> ElsaParser::parse_expression()
		{
			return parse_expression(0);
		}

		std::unique_ptr<Expression> ElsaParser::parse_expression(int precedence)
		{
			Parser* parser = nullptr;

			parser = get_ll2_expression_parser(current_token_->get_type(), peek_token()->get_type());
			if (parser == nullptr)
				parser = get_expression_parser(current_token_->get_type());

			if (parser == nullptr)
				throw ParsingException(L"Invalid token", current_token_.get());

			if (is_member_access())
			{
				// Struct access parser
				parser = get_ll2_expression_parser(TokenType::Identifier, TokenType::Dot);
			}

			auto left = std::unique_ptr<Expression>(parser->parse(this));

			while (precedence < get_precedence())
			{
				auto infix_parser = get_infix_parser(current_token()->get_type());
				left = std::unique_ptr<Expression>(infix_parser->parse(this, std::move(left)));
			}

			return left;
		}

		ScopedExpression* ElsaParser::current_scope()
		{
			if (current_scope_ == nullptr)
				throw ParsingException(L"No scope defined", current_token_.get());

			return current_scope_;
		}

		void ElsaParser::set_current_scope(ScopedExpression* scope)
		{
			current_scope_ = scope;
		}

		void ElsaParser::reset_current_scope()
		{
			current_scope_ = nullptr;
		}

		StructTable& ElsaParser::struct_table()
		{
			if (parent_ == nullptr)
				return struct_table_;

			return parent_->struct_table();
		}

		FunctionTable& ElsaParser::function_table()
		{
			if (parent_ == nullptr)
				return function_table_;

			return parent_->function_table();
		}

		TypeChecker & ElsaParser::type_checker()
		{
			return type_checker_;
		}

		void ElsaParser::consume(TokenType type)
		{
			if(current_token()->get_type() != type)
				throw ParsingException(L"Unexpected token", current_token_.get());

			next_token();
		}

		void ElsaParser::consume()
		{
			next_token();
		}

		Token* ElsaParser::current_token()
		{
			return current_token_.get();
		}

		Token* ElsaParser::peek_token()
		{
			return lexer_->peek_token();
		}

		void ElsaParser::set_current_type(const ElsaType* type)
		{
			current_type_ = type;
		}

		const ElsaType* ElsaParser::current_type() const
		{
			return current_type_;
		}

		void ElsaParser::set_current_struct(StructDeclarationExpression* sde)
		{
			current_struct_ = sde;
		}

		const StructDeclarationExpression* ElsaParser::current_struct() const
		{
			return current_struct_;
		}

		ElsaType* ElsaParser::current_struct_type()
		{
			if (current_struct_ == nullptr)
				return nullptr;

			return type_checker().get_expression_type(current_struct_);
		}

		ElsaParser::ElsaParser(ElsaParser* parent, Lexer* lexer)
			:
			parent_(parent),
			lexer_(std::unique_ptr<Lexer>(lexer)),
			current_scope_(nullptr),
			type_checker_(this),
			current_type_(nullptr),
			current_struct_(nullptr)
		{
			initialize_grammar();
			next_token();
		}

		void ElsaParser::next_token()
		{
			current_token_ = lexer_->next_token();
		}

		Parser* ElsaParser::get_expression_parser(TokenType type)
		{
			auto it = expression_parsers_.find(type);
			if (it != expression_parsers_.end())
			{
				return it->second.get();
			}

			return nullptr;
		}

		Parser* ElsaParser::get_ll2_expression_parser(TokenType first, TokenType second)
		{
			for (auto& entry : ll2_expression_parsers_)
			{
				if (entry->first == first && entry->second == second)
					return entry->parser.get();
			}

			return nullptr;
		}

		Parser* ElsaParser::get_statement_parser(TokenType type)
		{
			auto it = statement_parsers_.find(type);
			if (it != statement_parsers_.end())
			{
				return it->second.get();
			}

			return nullptr;
		}

		InfixParser* ElsaParser::get_infix_parser(TokenType type)
		{
			auto it = infix_parsers_.find(type);
			if (it != infix_parsers_.end())
			{
				return it->second.get();
			}

			return nullptr;
		}

		int ElsaParser::get_precedence()
		{
			auto infix_parser = get_infix_parser(current_token()->get_type());
			if (infix_parser != nullptr)
				return infix_parser->precedence();

			return 0;
		}

		void ElsaParser::register_expression_parser(TokenType type, Parser* parser)
		{
			expression_parsers_.insert(std::pair<TokenType, std::unique_ptr<Parser>>(type, std::unique_ptr<Parser>(parser)));
		}

		void ElsaParser::register_ll2_expression_parser(TokenType first, TokenType second, Parser* parser)
		{
			ll2_expression_parsers_.push_back(std::make_unique<LL2Entry>(first, second, parser));
		}

		void ElsaParser::register_statement_parser(TokenType type, Parser* parser)
		{
			statement_parsers_.insert(std::pair<TokenType, std::unique_ptr<Parser>>(type, std::unique_ptr<Parser>(parser)));
		}

		void ElsaParser::register_infix_parser(TokenType type, InfixParser* parser)
		{
			infix_parsers_.insert(std::pair<TokenType, std::unique_ptr<InfixParser>>(type, std::unique_ptr<InfixParser>(parser)));
		}

		void ElsaParser::register_prefix_parser(TokenType type)
		{
			register_expression_parser(type, new PrefixOperatorParser());
		}

		void ElsaParser::register_postfix_parser(TokenType type, InfixParser* parser)
		{
			register_infix_parser(type, parser);
		}

		void ElsaParser::initialize_grammar()
		{
			// Statements
			register_statement_parser(TokenType::Func, new FuncDeclarationParser());
			register_statement_parser(TokenType::Native, new FuncDeclarationParser());
			register_statement_parser(TokenType::Struct, new StructDeclarationParser());

			// LL2 Expressions
			register_ll2_expression_parser(TokenType::Identifier, TokenType::Dot, new StructAccessParser());
			register_ll2_expression_parser(TokenType::Identifier, TokenType::LParen, new FuncCallParser());
			register_ll2_expression_parser(TokenType::Identifier, TokenType::LSBracket, new ArrayAccessParser());
			register_ll2_expression_parser(TokenType::Identifier, TokenType::Identifier, new VariableDeclarationParser());

			register_ll2_expression_parser(TokenType::Int, TokenType::LParen, new TypeCastParser());
			register_ll2_expression_parser(TokenType::Float, TokenType::LParen, new TypeCastParser());
			register_ll2_expression_parser(TokenType::Char, TokenType::LParen, new TypeCastParser());

			// Expressions
			register_expression_parser(TokenType::Func, new AnonymousFuncDeclarationParser());
			register_expression_parser(TokenType::Var, new VariableDeclarationParser());
			register_expression_parser(TokenType::Int, new VariableDeclarationParser());
			register_expression_parser(TokenType::Float, new VariableDeclarationParser());
			register_expression_parser(TokenType::Char, new VariableDeclarationParser());
			register_expression_parser(TokenType::Bool, new VariableDeclarationParser());
			register_expression_parser(TokenType::Identifier, new IdentifierParser());
			register_expression_parser(TokenType::IntegerLiteral, new LiteralParser());
			register_expression_parser(TokenType::FloatLiteral, new LiteralParser());
			register_expression_parser(TokenType::CharLiteral, new LiteralParser());
			register_expression_parser(TokenType::BoolLiteral, new LiteralParser());
			register_expression_parser(TokenType::StringLiteral, new LiteralParser());
			register_expression_parser(TokenType::New, new CreateStructParser());
			register_expression_parser(TokenType::If, new ConditionalParser());
			register_expression_parser(TokenType::Loop, new LoopParser());
			register_expression_parser(TokenType::Return, new ReturnParser());
			register_expression_parser(TokenType::This, new StructAccessParser());

			// Prefix
			register_prefix_parser(TokenType::Exclamation);

			// Infix
			register_infix_parser(TokenType::Plus, new BinaryOperatorParser(Precedence::Sum));
			register_infix_parser(TokenType::Minus, new BinaryOperatorParser(Precedence::Sum));
			register_infix_parser(TokenType::Slash, new BinaryOperatorParser(Precedence::Product));
			register_infix_parser(TokenType::Asterix, new BinaryOperatorParser(Precedence::Product));
			register_infix_parser(TokenType::DoubleAmpersand, new BinaryOperatorParser(Precedence::ConditionalAnd));
			register_infix_parser(TokenType::DoubleVerticalBar, new BinaryOperatorParser(Precedence::ConditionalOr));

			register_infix_parser(TokenType::DoubleEquals, new BinaryOperatorParser(Precedence::Equality));
			register_infix_parser(TokenType::NotEquals, new BinaryOperatorParser(Precedence::Equality));

			register_infix_parser(TokenType::LessThan, new BinaryOperatorParser(Precedence::Relational));
			register_infix_parser(TokenType::GreaterThan, new BinaryOperatorParser(Precedence::Relational));
			register_infix_parser(TokenType::LessThanEquals, new BinaryOperatorParser(Precedence::Relational));
			register_infix_parser(TokenType::GreaterThanEquals, new BinaryOperatorParser(Precedence::Relational));

			register_infix_parser(TokenType::Equals, new AssignmentParser());

			// Postfix
			register_postfix_parser(TokenType::PlusPlus, new PostfixOperatorParser(Precedence::Unary));
			register_postfix_parser(TokenType::MinusMinus, new PostfixOperatorParser(Precedence::Unary));
		}

		void ElsaParser::initialize_default_imports()
		{
			import_source_file(L"std/system");
			import_source_file(L"std/string");
		}

		void ElsaParser::parse_import_statement()
		{
			consume(TokenType::Import);
			auto filename = current_token_->get_value();
			consume(TokenType::StringLiteral);
			consume(TokenType::Semicolon);

			if (already_imported(filename))
				return;

			import_source_file(filename);
		}

		void ElsaParser::import_source_file(const std::wstring& filename)
		{
			auto filename_with_extension = filename + L".elsa";
			auto parser = ElsaParser(this, new Lexer(new SourceFile(filename_with_extension.c_str())));
			parser.parse(get_root_program());
			imported_files_root().push_back(filename);
		}

		void ElsaParser::parse(Program* program)
		{
			while (current_token_->get_type() != TokenType::END)
			{
				program->add_statement(parse_statement());
			}
		}

		bool ElsaParser::already_imported(const std::wstring& filename)
		{
			const auto imported_files = imported_files_root();
			auto it = std::find(imported_files.begin(), imported_files.end(), filename);
			return it != imported_files.end();
		}

		std::vector<std::wstring>& ElsaParser::imported_files_root()
		{
			if (parent_ == nullptr)
				return imported_files_;

			return parent_->imported_files_root();
		}

		Program* ElsaParser::get_root_program()
		{
			if (parent_ == nullptr)
				return program_.get();

			return parent_->get_root_program();
		}

		bool ElsaParser::is_member_access()
		{
			if (current_struct() != nullptr && current_token_->get_type() == TokenType::Identifier)
			{
				auto access_type = std::unique_ptr<ElsaType>(type_checker().get_access_type(current_struct_type(), current_token_->get_value(), false));
				if (access_type.get() != nullptr)
					return true;
			}

			return false;
		}
	}
}
