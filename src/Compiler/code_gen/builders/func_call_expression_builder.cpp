#include "func_call_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void FuncCallExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, FuncCallExpression* expression)
		{
			for (auto& arg : expression->get_args())
			{
				arg->accept(visitor);
			}

			auto fi = program->get_func(expression->get_name());
			program->emit(OpCode::call);
			program->emit(static_cast<int>(fi->get_addr()));
		}

	}
}
