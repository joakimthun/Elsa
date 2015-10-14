#include "compiler.h"

namespace elsa {
	namespace compiler {

		void Compiler::compile(const char* filename)
		{
			auto source_file = SourceFile(filename);
			auto lexer = Lexer(&source_file);
			auto parser = ElsaParser(&lexer);
		}

	}
}
