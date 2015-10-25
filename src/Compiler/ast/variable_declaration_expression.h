#pragma once

#include <string>
#include <memory>

#include "expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class VariableDeclarationExpression : public Expression
		{
		public:
			VariableDeclarationExpression(const std::wstring& name, ElsaType* type, Expression* expression);

			const std::wstring& get_name() const;
			const ElsaType* get_type() const;
			Expression* get_expression() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring name_;
			std::unique_ptr<ElsaType> type_;
			std::unique_ptr<Expression> expression_;
		};
	}
}
