#include "conditional_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void ConditionalExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, ConditionalExpression* expression)
		{
			expression->get_condition()->accept(visitor);

			// Push true
			program->emit(OpCode::bconst);
			program->emit(1);

			// If not equal -> branch
			program->emit(OpCode::br_bneq);
			auto branch_addr_index = program->mark_index();

			for (auto& exp : expression->get_if_body())
			{
				exp->accept(visitor);
			}

			if (expression->has_else_body())
			{
				program->emit(branch_addr_index, program->get_next_instruction_index());

				for (auto& exp : expression->get_else_body())
				{
					exp->accept(visitor);
				}
			}
			else
			{
				program->emit(branch_addr_index, program->get_next_instruction_index());
			}
		}

	}
}
