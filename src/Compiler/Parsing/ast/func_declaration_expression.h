#pragma once

#include <string>
#include <vector>
#include <memory>

#include "expression.h"

namespace elsa {
	namespace compiler {

		class FuncDeclarationExpression : public Expression
		{
		public:
			FuncDeclarationExpression(const std::wstring& name);

			void add_expression(Expression* expression);

		private:
			std::wstring name_;
			std::vector<std::unique_ptr<Expression>> body_;
		};
	}
}
