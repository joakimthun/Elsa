#pragma once

#include <string>
#include <memory>

#include "expression.h"
#include "typed_expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class FieldAccessExpression : public Expression, public TypedExpression
		{
		public:
			FieldAccessExpression(const std::wstring& name);

			void set_type(ElsaType* type);

			const std::wstring& get_name() const override;
			const ElsaType* get_type() const override;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring name_;
			std::unique_ptr<ElsaType> type_;
		};

	}
}

