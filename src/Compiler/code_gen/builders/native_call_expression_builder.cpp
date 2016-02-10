#include "native_call_expression_builder.h"

#include "../vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void NativeCallExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, FuncCallExpression* expression)
		{
			for (auto& arg : expression->get_args())
			{
				arg->accept(visitor);
			}

			program->emit(OpCode::ncall);
			auto nf = visitor->native_function_table().get(expression->get_name());

			if (nf == nullptr)
				throw CodeGenException("Undefined native function");

			program->emit(static_cast<int>(nf->get_index()));
		}

	}
}

