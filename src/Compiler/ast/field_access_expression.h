#pragma once

#include <string>
#include <memory>

#include "expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class FieldAccessExpression : public Expression
		{
		public:
			FieldAccessExpression(const std::wstring& name);

			void set_type(ElsaType* type);

			const std::wstring& get_name() const;
			const ElsaType* get_type() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring name_;
			std::unique_ptr<ElsaType> type_;
		};

	}
}

