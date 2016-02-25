#include "vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		VMExpressionVisitor::VMExpressionVisitor(TypeChecker* type_checker)
			:
			vm_program_(std::make_unique<VMProgram>()),
			type_checker_(type_checker)
		{
			Builtin::init(vm_program_.get());
		}

		void VMExpressionVisitor::visit(FuncDeclarationExpression* expression)
		{
			if (expression->is_native())
			{
				return;
			}

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
			if (!expression->stack_invoke() && expression->get_func_declaration_expression()->is_native())
			{
				NativeCallExpressionBuilder::build(vm_program_.get(), this, expression);
			}
			else
			{
				FuncCallExpressionBuilder::build(vm_program_.get(), this, expression);
			}
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

		void VMExpressionVisitor::visit(ArrayInitializerListExpression* expression)
		{
			ArrayInitializerListExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(StringLiteralExpression* expression)
		{
			LiteralExpressionBuilder::build(vm_program_.get(), expression);
		}

		void VMExpressionVisitor::visit(TypeCastExpression* expression)
		{
			TypeCastExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(StructInitializerListExpression* expression)
		{
			StructInitializerListExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(GroupedExpression* expression)
		{
			GroupedExpressionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(ByteLiteralExpression* expression)
		{

		}

		ScopedExpression* VMExpressionVisitor::current_scope()
		{
			return current_scope_;
		}

		void VMExpressionVisitor::push_new_scope(ScopedExpression* scope)
		{
			current_scope_ = scope;
		}

		void VMExpressionVisitor::pop_current_scope()
		{
			if (current_scope_ == nullptr)
				throw CodeGenException(L"VMExpressionVisitor::pop_current_scope: No scope to pop");

			current_scope_ = current_scope_->parent();
		}

		std::unique_ptr<VMProgram> VMExpressionVisitor::release_program()
		{
			return std::move(vm_program_);
		}

		NativeFunctionTable& VMExpressionVisitor::native_function_table()
		{
			return native_function_table_;
		}

		TypeChecker* VMExpressionVisitor::type_checker()
		{
			return type_checker_;
		}

		void VMExpressionVisitor::set_current_type(const ElsaType* type)
		{
			current_type_ = type;
		}

		const ElsaType* VMExpressionVisitor::current_type()
		{
			return current_type_;
		}

	}
}