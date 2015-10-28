#pragma once

#include <string>

#include "expression.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class ElsaInvokeExpression : public Expression
		{
		public:
			ElsaInvokeExpression(const std::wstring& function_name);

			const std::wstring& get_function_name() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring function_name_;
		};
	}
}
