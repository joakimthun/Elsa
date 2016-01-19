#pragma once

#include <string>
#include <memory>

#include "expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class IdentifierExpression : public Expression
		{
		public:
			IdentifierExpression(const std::wstring& name);

			void set_type(ElsaType* type);

			const std::wstring& get_name() const;
			ElsaType* get_type();

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring name_;
			std::unique_ptr<ElsaType> type_;
		};

	}
}
