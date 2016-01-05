#include "array_declaration_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void ArrayDeclarationExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, ArrayDeclarationExpression* expression)
		{
			program->emit(OpCode::iconst);
			program->emit(10);
			program->emit(OpCode::new_arr);

			auto type = expression->get_type()->get_struct_declaration_expression()->get_generic_type();
			program->emit(static_cast<int>(type->get_vm_type()));
		}

	}
}
