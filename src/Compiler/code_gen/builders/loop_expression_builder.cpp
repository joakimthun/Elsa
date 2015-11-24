#include "loop_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void LoopExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, LoopExpression* expression)
		{
			// Declare the loop variable
			expression->get_variable_expression()->accept(visitor);

			// Set the address to jump to after each iteration
			auto before_condition_addr_index = program->mark_index();

			// Generate the loop condition
			expression->get_condition()->accept(visitor);

			// Push true
			program->emit(OpCode::iconst);
			program->emit(1);

			// If not equal -> branch
			program->emit(OpCode::br_ineq);
			auto after_loop_addr_index = program->mark_index();

			for (auto& exp : expression->get_body())
			{
				exp->accept(visitor);
			}

			expression->get_post_expression()->accept(visitor);

			program->emit(OpCode::br);
			program->emit(before_condition_addr_index);

			// Set the address to jump to if the loop condition fails
			program->emit(after_loop_addr_index, program->get_next_instruction_index());
		}

	}
}