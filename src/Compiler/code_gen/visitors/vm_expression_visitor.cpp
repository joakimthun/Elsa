#include "vm_expression_visitor.h"

#include "../../ast/func_declaration_expression.h"
#include "../../ast/variable_declaration_expression.h"
#include "../../ast/binary_operator_expression.h"
#include "../../ast/integer_literal_expression.h"

namespace elsa {
	namespace compiler {

		VMExpressionVisitor::VMExpressionVisitor(FunctionTable* function_table, StructTable* struct_table)
			:
			function_table_(function_table),
			struct_table_(struct_table),
			vm_program_(std::make_unique<VMProgram>()),
			scope_nesting_(0),
			current_function_(nullptr)
		{}

		void VMExpressionVisitor::visit(FuncDeclarationExpression* expression)
		{
			FunctionDeclarationExpressionBuilder::build(vm_program_.get(), this, expression);
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

		void VMExpressionVisitor::visit(ElsaInvokeExpression* expression)
		{
			ElsaInvokeExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(IdentifierExpression* expression)
		{
			IdentifierExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(FloatLiteralExpression* expression)
		{
			LiteralExpressionBuilder::build(vm_program_.get(), expression);
		}

		void VMExpressionVisitor::visit(CharLiteralExpression* expression)
		{
			LiteralExpressionBuilder::build(vm_program_.get(), expression);
		}

		void VMExpressionVisitor::visit(StructDeclarationExpression * expression)
		{
			StructDeclarationExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(CreateStructExpression * expression)
		{
			CreateStructExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		std::unique_ptr<VMProgram> VMExpressionVisitor::release_program()
		{
			return std::move(vm_program_);
		}

		NativeFunctionTable& VMExpressionVisitor::native_function_table()
		{
			return native_function_table_;
		}

		StructTable* VMExpressionVisitor::struct_table()
		{
			return struct_table_;
		}

		FunctionTable* VMExpressionVisitor::function_table()
		{
			return function_table_;
		}

		void VMExpressionVisitor::increment_scope_nesting()
		{
			scope_nesting_++;
		}

		void VMExpressionVisitor::reset_scope_nesting()
		{
			scope_nesting_ = 0;
		}

		const LocalSymbol* VMExpressionVisitor::get_local(const std::wstring& name) const
		{
			if (current_function_ == nullptr)
				throw CodeGenException("No current function is defined");

			if (current_function_->locals().scope_has_entry(scope_nesting_, name))
				return current_function_->locals().get_local(scope_nesting_, name);

			throw CodeGenException("No local defined with that name and scope nesting");
		}

		void VMExpressionVisitor::set_current_function(const std::wstring& name)
		{
			if (!function_table_->has_entry(name))
				throw CodeGenException("No function with that name defined");

			current_function_ = function_table_->get(name);
		}

		void VMExpressionVisitor::reset_current_function()
		{
			current_function_ = nullptr;
		}

	}
}