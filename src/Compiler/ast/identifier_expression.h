#pragma once

#include <string>
#include <memory>

#include "expression.h"
#include "../types/elsa_type.h"
#include "typed_expression.h"

namespace elsa {
	namespace compiler {

		class IdentifierExpression : public Expression, public TypedExpression
		{
		public:
			IdentifierExpression(const std::wstring& name);

			void set_type(ElsaType* type);

			const std::wstring& get_name() const;
			const ElsaType* get_type() const;
			ExpressionType get_expression_type() const override;

			void set_from_closure(bool from_closure);
			bool get_from_closure() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring name_;
			std::unique_ptr<ElsaType> type_;
			bool from_closure_;
		};

	}
}
