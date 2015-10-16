#include "code_gen.h"

namespace elsa {
	namespace compiler {

		CodeGen::CodeGen(Program* program) 
			:
			program_(program)
		{}

		void CodeGen::generate()
		{
			auto visitor = std::make_unique<VMExpressionVisitor>();

			for (auto& s : program_->get_statements())
			{
				s->accept(visitor.get());
			}
		}

	}
}

