#include "create_struct_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		CreateStructExpression::CreateStructExpression(const std::wstring& name)
			:
			struct_name_(name)
		{}

		const std::wstring& CreateStructExpression::get_struct_name() const
		{
			return struct_name_;
		}

		void CreateStructExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}

