#include "struct_initializer_list_expression.h"

#include "../expression_visitor.h"

namespace elsa {
	namespace compiler {

		void StructInitializerListExpression::set_create_struct_expression(std::unique_ptr<CreateStructExpression> exp)
		{
			create_struct_expression_ = std::move(exp);
		}

		const CreateStructExpression* StructInitializerListExpression::get_create_struct_expression() const
		{
			return create_struct_expression_.get();
		}

		void StructInitializerListExpression::add_value_expression(std::unique_ptr<FieldInitializerExpression> exp)
		{
			values_.push_back(std::move(exp));
		}

		std::vector<std::unique_ptr<FieldInitializerExpression>>& StructInitializerListExpression::get_value_expressions()
		{
			return values_;
		}

		void StructInitializerListExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
	}
}
