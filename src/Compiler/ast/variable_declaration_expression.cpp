#include "variable_declaration_expression.h"

#include "../expression_visitor.h"

namespace elsa {
	namespace compiler {

		VariableDeclarationExpression::VariableDeclarationExpression(const std::wstring& name, ElsaType* type, std::unique_ptr<Expression> expression)
			:
			name_(name),
			type_(type),
			expression_(std::move(expression))
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

		void VariableDeclarationExpression::set_expression(std::unique_ptr<Expression> expression)
		{
			expression_ = std::move(expression);
		}

		Expression* VariableDeclarationExpression::release_expression()
		{
			return expression_.release();
		}

		void VariableDeclarationExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
	}
}

