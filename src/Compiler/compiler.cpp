#include "compiler.h"

namespace elsa {
	namespace compiler {

		void Compiler::compile(const char* filename)
		{
			auto source_file = SourceFile(filename);
			auto lexer = Lexer(&source_file);
			auto parser = ElsaParser(&lexer);
			auto program = std::unique_ptr<Program>(parser.parse());
			auto cg = CodeGen(program.get());
			cg.generate();
		}

	}
}
