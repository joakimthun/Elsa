#include "vm_expression_visitor.h"

#include "../../ast/func_declaration_expression.h"
#include "../../ast/variable_declaration_expression.h"
#include "../../ast/binary_operator_expression.h"
#include "../../ast/integer_literal_expression.h"

namespace elsa {
	namespace compiler {

		VMExpressionVisitor::VMExpressionVisitor()
			:
			vm_program_(std::make_unique<VMProgram>())
		{}

		void VMExpressionVisitor::visit(FuncDeclarationExpression* expression)
		{
			FunctionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(VariableDeclarationExpression* expression)
		{

		}

		void VMExpressionVisitor::visit(BinaryOperatorExpression* expression)
		{

		}

		void VMExpressionVisitor::visit(IntegerLiteralExpression* expression)
		{

		}

		void VMExpressionVisitor::push_new_scope()
		{
			local_table_.push_back(std::make_unique<LocalTable>());
		}

		void VMExpressionVisitor::pop_current_scope()
		{
			local_table_.pop_back();
		}

		void VMExpressionVisitor::push_current(LocalSymbol* symbol)
		{
			local_table_.back()->add(symbol->get_name(), symbol);
		}

		bool VMExpressionVisitor::has_entry(std::wstring name)
		{
			return local_table_.back()->has_entry(name);
		}

	}
}