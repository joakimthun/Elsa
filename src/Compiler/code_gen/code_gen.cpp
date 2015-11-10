#include "code_gen.h"

namespace elsa {
	namespace compiler {

		CodeGen::CodeGen(Program* program) 
			:
			program_(program)
		{}

		std::unique_ptr<VMProgram> CodeGen::generate()
		{
			auto visitor = std::make_unique<VMExpressionVisitor>(program_->function_table(), program_->struct_table());

			for (auto& s : program_->get_statements())
			{
				s->accept(visitor.get());
			}

			return visitor->release_program();
		}

	}
}

