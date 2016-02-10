#include "conditional_expression_builder.h"

#include "../vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void ConditionalExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, ConditionalExpression* expression)
		{
			expression->get_condition()->accept(visitor);

			// Push true
			program->emit(OpCode::iconst);
			program->emit(1);

			// If not equal -> branch
			program->emit(OpCode::br_ineq);
			auto after_if_addr_index = program->mark_index();

			visitor->push_new_scope(expression->get_if_scope());

			for (auto& exp : expression->get_if_body())
			{
				exp->accept(visitor);
			}

			visitor->pop_current_scope();

			// If we execute the if branch we jump past the else branch(if there is one)
			program->emit(OpCode::br);
			auto if_end_addr_index = program->mark_index();

			if (expression->has_else_body())
			{
				visitor->push_new_scope(expression->get_if_scope());

				program->emit(after_if_addr_index, static_cast<int>(program->get_next_instruction_index()));

				for (auto& exp : expression->get_else_body())
				{
					exp->accept(visitor);
				}

				program->emit(if_end_addr_index, static_cast<int>(program->get_next_instruction_index()));

				visitor->pop_current_scope();
			}
			else
			{
				program->emit(after_if_addr_index, static_cast<int>(program->get_next_instruction_index()));
				program->emit(if_end_addr_index, static_cast<int>(program->get_next_instruction_index()));
			}
		}

	}
}
