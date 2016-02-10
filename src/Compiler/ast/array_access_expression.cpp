#include "array_access_expression.h"

#include "../expression_visitor.h"

namespace elsa {
	namespace compiler {

		void ArrayAccessExpression::set_identifier_expression(std::unique_ptr<IdentifierExpression> identifier_expression)
		{
			identifier_expression_ = std::move(identifier_expression);
		}

		void ArrayAccessExpression::set_index_expression(std::unique_ptr<Expression> expression)
		{
			index_expression_ = std::move(expression);
		}

		void ArrayAccessExpression::set_struct_access_expression(StructAccessExpression* expression)
		{
			struct_access_expression_ = std::unique_ptr<StructAccessExpression>(expression);
		}

		IdentifierExpression* ArrayAccessExpression::get_identifier_expression() const
		{
			return identifier_expression_.get();
		}

		Expression* ArrayAccessExpression::get_index_expression() const
		{
			return index_expression_.get();
		}

		StructAccessExpression * ArrayAccessExpression::get_struct_access_expression() const
		{
			return struct_access_expression_.get();
		}

		const std::wstring& ArrayAccessExpression::get_name() const
		{
			return identifier_expression_->get_name();
		}

		const ElsaType* ArrayAccessExpression::get_type() const
		{
			return identifier_expression_->get_type();
		}

		ExpressionType ArrayAccessExpression::get_expression_type() const
		{
			return ExpressionType::ArrayAccess;
		}

		void ArrayAccessExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
	}
}
