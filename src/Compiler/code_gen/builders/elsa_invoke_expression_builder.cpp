#include "elsa_invoke_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void ElsaInvokeExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, ElsaInvokeExpression* expression)
		{
			const auto& native_function_info = visitor->get_native_function_table().get(expression->get_function_name());

			std::size_t index = 0;
			for (auto& arg : expression->get_args())
			{
				auto elsa_type = TypeChecker::get_expression_type(arg.get());

				if (!native_function_info->is_valid_arg_type(index, elsa_type->get_type()))
					throw CodeGenException("Invalid argument type passed to native function");

				arg->accept(visitor);

				index++;
			}

			program->emit(OpCode::elsa);
			program->emit(static_cast<int>(OType::Int));
			program->emit(static_cast<int>(native_function_info->get_index()));

		}

	}
}

