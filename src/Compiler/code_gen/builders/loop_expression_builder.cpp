#include "loop_expression_builder.h"

#include "../vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void LoopExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, LoopExpression* expression)
		{
			visitor->push_new_scope(expression);

			if (expression->get_type() == LoopType::For)
				build_for_loop(program, visitor, expression);
			else
				build_while_loop(program, visitor, expression);

			visitor->pop_current_scope();
		}

		void LoopExpressionBuilder::build_for_loop(VMProgram* program, VMExpressionVisitor* visitor, LoopExpression* expression)
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

			build_loop_body(program, visitor, expression);

			expression->get_post_expression()->accept(visitor);

			program->emit(OpCode::br);
			program->emit(static_cast<int>(before_condition_addr_index));

			// Set the address to jump to if the loop condition fails
			program->emit(after_loop_addr_index, static_cast<int>(program->get_next_instruction_index()));
		}

		void LoopExpressionBuilder::build_while_loop(VMProgram* program, VMExpressionVisitor* visitor, LoopExpression* expression)
		{
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

			build_loop_body(program, visitor, expression);

			program->emit(OpCode::br);
			program->emit(static_cast<int>(before_condition_addr_index));

			// Set the address to jump to if the loop condition fails
			program->emit(after_loop_addr_index, static_cast<int>(program->get_next_instruction_index()));
		}

		void LoopExpressionBuilder::build_loop_body(VMProgram* program, VMExpressionVisitor* visitor, LoopExpression* expression)
		{
			for (auto& exp : expression->get_body())
			{
				exp->accept(visitor);
			}
		}

	}
}