#include "compiler.h"

namespace elsa {
	namespace compiler {

		VMProgram* Compiler::compile(const char* filename)
		{
			auto parser = ElsaParser(new Lexer(new SourceFile(filename)));
			auto program = std::unique_ptr<Program>(parser.parse());
			auto cg = CodeGen(program.get());
			return cg.generate();
		}

	}
}
