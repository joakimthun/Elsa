#pragma once

#include <string>
#include <memory>

#include "expression.h"

namespace elsa {
	namespace compiler {

		class VariableDeclarationExpression : public Expression
		{
		public:
			VariableDeclarationExpression(const std::wstring& name, const std::wstring& type, Expression* expression);

			const std::wstring& get_name() const;
			const std::wstring& get_type() const;
			Expression* get_expression() const;

		private:
			std::wstring name_;
			std::wstring type_;
			std::unique_ptr<Expression> expression_;
		};
	}
}
