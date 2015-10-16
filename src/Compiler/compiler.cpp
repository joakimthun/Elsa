#include "compiler.h"

namespace elsa {
	namespace compiler {

		void Compiler::compile(const char* filename)
		{
			auto parser = ElsaParser(new Lexer(new SourceFile(filename)));
			auto program = std::unique_ptr<Program>(parser.parse());
			auto cg = CodeGen(program.get());
			cg.generate();
		}

	}
}
