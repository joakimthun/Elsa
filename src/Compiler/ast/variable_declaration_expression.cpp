#include "variable_declaration_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		VariableDeclarationExpression::VariableDeclarationExpression(const std::wstring& name, ElsaType* type, Expression* expression)
			:
			name_(name),
			type_(type),
			expression_(std::unique_ptr<Expression>(expression))
		{}

		const std::wstring& VariableDeclarationExpression::get_name() const
		{
			return name_;
		}

		const ElsaType* VariableDeclarationExpression::get_type() const
		{
			return type_.get();
		}

		Expression* VariableDeclarationExpression::get_expression() const
		{
			return expression_.get();
		}

		void VariableDeclarationExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
	}
}

