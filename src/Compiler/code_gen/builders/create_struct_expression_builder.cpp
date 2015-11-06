#include "create_struct_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void CreateStructExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, CreateStructExpression* expression)
		{
			if (!visitor->has_struct_entry(expression->get_struct_name()))
				throw CodeGenException("No struct with that name has been defined");

			auto struct_entry = visitor->get_struct(expression->get_struct_name());

			program->emit(OpCode::new_struct);
			program->emit(static_cast<int>(struct_entry->get_index()));
		}

	}
}
