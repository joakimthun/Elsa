#include "create_struct_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		CreateStructExpression::CreateStructExpression(const std::wstring& name, ElsaType* type)
			:
			struct_name_(name),
			type_(std::unique_ptr<ElsaType>(type))
		{}

		const std::wstring& CreateStructExpression::get_struct_name() const
		{
			return struct_name_;
		}

		const ElsaType* CreateStructExpression::get_type() const
		{
			return type_.get();
		}

		void CreateStructExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}

