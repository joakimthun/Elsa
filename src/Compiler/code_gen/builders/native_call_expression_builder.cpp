#include "native_call_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void NativeCallExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, FuncCallExpression* expression)
		{
			const auto& native_function_info = visitor->native_function_table().get(expression->get_name());

			std::size_t index = 0;
			for (auto& arg : expression->get_args())
			{
				arg->accept(visitor);

				index++;
			}

			program->emit(OpCode::ncall);
			auto nf = visitor->native_function_table().get(expression->get_name());

			if (nf == nullptr)
				throw CodeGenException("Undefined native function");

			program->emit(static_cast<int>(nf->get_index()));
		}

	}
}

