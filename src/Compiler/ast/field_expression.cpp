#include "field_expression.h"

namespace elsa {
	namespace compiler {

		FieldExpression::FieldExpression()
			:
			is_array_(false)
		{
		}

		FieldExpression::FieldExpression(const std::wstring& name, const ElsaType* type, std::size_t index)
			:
			name_(name),
			type_(new ElsaType(type)),
			index_(index),
			is_array_(false)
		{
		}

		void FieldExpression::set_name(const std::wstring& name)
		{
			name_ = name;
		}

		void FieldExpression::set_type(ElsaType* type)
		{
			type_ = std::unique_ptr<ElsaType>(type);
		}

		void FieldExpression::set_index(std::size_t index)
		{
			index_ = index;
		}

		void FieldExpression::set_is_array(bool is_array)
		{
			is_array_ = is_array;
		}

		const std::wstring& FieldExpression::get_name() const
		{
			return name_;
		}

		const ElsaType* FieldExpression::get_type() const
		{
			return type_.get();
		}

		std::size_t FieldExpression::get_index() const
		{
			return index_;
		}

		bool FieldExpression::get_is_array() const
		{
			return is_array_;
		}

		void FieldExpression::accept(ExpressionVisitor* visitor)
		{
			//visitor->visit(this);
			throw ElsaException("No visit method defined for FieldExpression");
		}
	}
}
