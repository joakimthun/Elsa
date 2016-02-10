#include "loop_expression.h"

#include "../expression_visitor.h"

namespace elsa {
	namespace compiler {

		LoopExpression::LoopExpression(ScopedExpression* parent) : ScopedExpression(parent)
		{
		}

		void LoopExpression::set_variable_expression(std::unique_ptr<Expression> expression)
		{
			variable_expression_ = std::move(expression);
		}

		void LoopExpression::set_condition(std::unique_ptr<Expression> expression)
		{
			condition_ = std::move(expression);
		}

		void LoopExpression::set_post_expression(std::unique_ptr<Expression> expression)
		{
			post_expression_ = std::move(expression);
		}

		void LoopExpression::add_to_body(std::unique_ptr<Expression> expression)
		{
			body_.push_back(std::move(expression));
		}

		Expression* LoopExpression::get_variable_expression()
		{
			return variable_expression_.get();
		}

		Expression* LoopExpression::get_condition()
		{
			return condition_.get();
		}

		Expression* LoopExpression::get_post_expression()
		{
			return post_expression_.get();
		}

		const std::vector<std::unique_ptr<Expression>>& LoopExpression::get_body() const
		{
			return body_;
		}

		void LoopExpression::set_type(LoopType type)
		{
			type_ = type;
		}

		LoopType LoopExpression::get_type()
		{
			return type_;
		}

		void LoopExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}
