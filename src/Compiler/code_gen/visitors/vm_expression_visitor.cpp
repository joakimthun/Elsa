#include "vm_expression_visitor.h"

#include "../../ast/func_declaration_expression.h"
#include "../../ast/variable_declaration_expression.h"
#include "../../ast/binary_operator_expression.h"
#include "../../ast/integer_literal_expression.h"

namespace elsa {
	namespace compiler {

		VMExpressionVisitor::VMExpressionVisitor()
			:
			vm_program_(std::make_unique<VMProgram>()),
			current_function_(nullptr)
		{}

		void VMExpressionVisitor::visit(FuncDeclarationExpression* expression)
		{
			FunctionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(VariableDeclarationExpression* expression)
		{
			VariableBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(BinaryOperatorExpression* expression)
		{
			BinaryOperatorExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(IntegerLiteralExpression* expression)
		{
			LiteralExpressionBuilder::build(vm_program_.get(), expression);
		}

		void VMExpressionVisitor::visit(ElsaInvokeExpression * expression)
		{
		}

		void VMExpressionVisitor::push_new_scope()
		{
			local_table_.push_back(std::make_unique<LocalTable>());
		}

		void VMExpressionVisitor::pop_current_scope()
		{
			if (local_table_.size() == 0)
				throw CodeGenException("Pop can not be called on an empty symbol table stack");

			local_table_.pop_back();
		}

		void VMExpressionVisitor::push_current_scope(const std::wstring& name, const ElsaType& type)
		{
			if (local_table_.size() == 0)
				throw CodeGenException("Push can not be called on an empty symbol table stack");

			auto& current_table = local_table_.back();
			auto local_index = current_table->get_next_index() + current_function_->get_num_args() + current_function_->get_num_locals();

			local_table_.back()->add(name, new LocalSymbol(name, local_index, type));
		}

		bool VMExpressionVisitor::current_scope_has_entry(std::wstring name)
		{
			if (local_table_.size() == 0)
				throw CodeGenException("The symbol table stack is empty");

			return local_table_.back()->has_entry(name);
		}

		const LocalSymbol* VMExpressionVisitor::get_from_current_scope(std::wstring name) const
		{
			return local_table_.back()->get(name);
		}

		std::unique_ptr<VMProgram> VMExpressionVisitor::release_program()
		{
			return std::move(vm_program_);
		}

		void VMExpressionVisitor::set_current_function(FunctionInfo* fi)
		{
			current_function_ = fi;
		}

		FunctionInfo * VMExpressionVisitor::get_current_function()
		{
			return current_function_;
		}

		void VMExpressionVisitor::reset_current_function()
		{
			current_function_ = nullptr;
		}

	}
}