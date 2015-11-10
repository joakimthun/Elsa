#include "create_struct_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void CreateStructExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, CreateStructExpression* expression)
		{
			auto si = program->get_struct(expression->get_struct_name());

			if (si == nullptr)
				throw CodeGenException("No struct with that name has been defined");

			program->emit(OpCode::new_struct);
			program->emit(static_cast<int>(si->get_index()));
		}

	}
}
