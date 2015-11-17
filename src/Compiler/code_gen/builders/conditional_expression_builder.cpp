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
			auto after_if_addr_index = program->mark_index();

			for (auto& exp : expression->get_if_body())
			{
				exp->accept(visitor);
			}

			// If we execute the if branch we jump past the else branch(if there is one)
			program->emit(OpCode::br);
			auto if_end_addr_index = program->mark_index();

			if (expression->has_else_body())
			{
				program->emit(after_if_addr_index, program->get_next_instruction_index());

				for (auto& exp : expression->get_else_body())
				{
					exp->accept(visitor);
				}

				program->emit(if_end_addr_index, program->get_next_instruction_index());
			}
			else
			{
				program->emit(after_if_addr_index, program->get_next_instruction_index());
				program->emit(if_end_addr_index, program->get_next_instruction_index());
			}
		}

	}
}
