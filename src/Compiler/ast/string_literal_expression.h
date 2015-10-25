#pragma once

#include <string>

#include "expression.h"

namespace elsa {
	namespace compiler {

		class StringLiteralExpression : public Expression
		{
		public:
			StringLiteralExpression(const std::wstring& value);

			const std::wstring& get_value() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring value_;
		};
	}
}
