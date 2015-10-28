#include "compiler.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<VMProgram> Compiler::compile(const char* filename)
		{
			auto parser = ElsaParser(new Lexer(new SourceFile(filename)));
			auto program = parser.parse();
			auto cg = CodeGen(program.get());
			return cg.generate();
		}

	}
}
