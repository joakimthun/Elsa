#include "compiler.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<VMProgram> Compiler::compile(const wchar_t* filename)
		{
			return compile_impl(filename);
		}

		std::unique_ptr<VMProgram> Compiler::compile(const char* filename)
		{
			auto w_fn = StringUtil::to_wchar(filename);
			return compile_impl(w_fn.c_str());
		}

		std::unique_ptr<VMProgram> Compiler::compile_impl(const wchar_t* filename)
		{
			auto parser = ElsaParser(new Lexer(new SourceFile(filename)));
			auto program = parser.parse();

			auto visitor = std::make_unique<ASTRewriteExpressionVisitor>(&parser);

			for (auto& statement : program->get_statements())
			{
				statement->accept(visitor.get());
			}

			for (auto& statement : visitor->get_statements())
			{
				program->add_statement_front(std::move(statement));
			}

			auto cg = CodeGen(program.get(), &parser.type_checker());
			return cg.generate();
		}

	}
}
