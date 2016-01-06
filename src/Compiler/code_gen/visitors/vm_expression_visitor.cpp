#include "vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		VMExpressionVisitor::VMExpressionVisitor()
			:
			vm_program_(std::make_unique<VMProgram>())
		{
			Builtin::init(vm_program_.get());
		}

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

		void VMExpressionVisitor::visit(StructDeclarationExpression* expression)
		{
			StructDeclarationExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(CreateStructExpression* expression)
		{
			CreateStructExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(StructAccessExpression* expression)
		{
			StructAccessExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(AssignmentExpression* expression)
		{
			AssignmentExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(FuncCallExpression* expression)
		{
			FuncCallExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(BoolLiteralExpression * expression)
		{
			LiteralExpressionBuilder::build(vm_program_.get(), expression);
		}

		void VMExpressionVisitor::visit(ConditionalExpression* expression)
		{
			ConditionalExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(LoopExpression* expression)
		{
			LoopExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(PostfixOperatorExpression* expression)
		{
			PostfixOperatorExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(ReturnExpression* expression)
		{
			ReturnExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(ArrayDeclarationExpression* expression)
		{
			ArrayDeclarationExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(ArrayAccessExpression* expression)
		{
			ArrayAccessExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		ScopedExpression* VMExpressionVisitor::current_scope()
		{
			if (current_scope_ == nullptr)
				throw CodeGenException("No scope defined");

			return current_scope_;
		}

		void VMExpressionVisitor::set_current_scope(ScopedExpression* scope)
		{
			current_scope_ = scope;
		}

		void VMExpressionVisitor::reset_current_scope()
		{
			current_scope_ = nullptr;
		}

		std::unique_ptr<VMProgram> VMExpressionVisitor::release_program()
		{
			return std::move(vm_program_);
		}

		NativeFunctionTable& VMExpressionVisitor::native_function_table()
		{
			return native_function_table_;
		}

	}
}