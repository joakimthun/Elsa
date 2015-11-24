#include "assignment_expression_builder.h"

#include "../../ast/struct_declaration_expression.h"
#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void AssignmentExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, AssignmentExpression* expression)
		{
			if (auto sae = dynamic_cast<StructAccessExpression*>(expression->get_left()))
			{
				auto field_index = StoreHelper::store_field(program, visitor, sae);
				expression->get_right()->accept(visitor);
				program->emit(OpCode::s_field);
				program->emit(static_cast<int>(field_index));
				return;
			}
			else if (auto ie = dynamic_cast<IdentifierExpression*>(expression->get_left()))
			{
				auto local_index = StoreHelper::store_local(program, visitor, ie);
				expression->get_right()->accept(visitor);

				program->emit(OpCode::s_local);
				program->emit(static_cast<int>(local_index));

				return;
			}

			throw CodeGenException("Not supported -> AssignmentExpressionBuilder");
		}

	}
}
