#include "argument_expression.h"

namespace elsa {
	namespace compiler {

		ArgumentExpression::ArgumentExpression()
		{
		}

		ArgumentExpression::ArgumentExpression(const std::wstring & name, const ElsaType * type)
			:
			name_(name),
			type_(std::make_unique<ElsaType>(type))
		{
		}

		void ArgumentExpression::set_name(const std::wstring& name)
		{
			name_ = name;
		}

		void ArgumentExpression::set_type(ElsaType* type)
		{
			type_ = std::unique_ptr<ElsaType>(type);
		}

		const std::wstring& ArgumentExpression::get_name() const
		{
			return name_;
		}

		const ElsaType* ArgumentExpression::get_type() const
		{
			return type_.get();
		}

		void ArgumentExpression::accept(ExpressionVisitor* visitor)
		{
			//visitor->visit(this);
			throw ElsaException("No visit method defined for ArgumentExpression");
		}
	}
}
