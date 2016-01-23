#include "code_gen.h"

namespace elsa {
	namespace compiler {

		CodeGen::CodeGen(Program* program, TypeChecker* type_checker)
			:
			program_(program),
			type_checker_(type_checker)
		{}

		std::unique_ptr<VMProgram> CodeGen::generate()
		{
			auto visitor = std::make_unique<VMExpressionVisitor>(type_checker_);

			for (auto& s : program_->get_statements())
			{
				s->accept(visitor.get());
			}

			return visitor->release_program();
		}

	}
}

