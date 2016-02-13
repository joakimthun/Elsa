#pragma once

#include <string>
#include <memory>
#include <utility>

#include "expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class VariableDeclarationExpression : public Expression
		{
		public:
			VariableDeclarationExpression(const std::wstring& name, ElsaType* type, std::unique_ptr<Expression> expression);

			const std::wstring& get_name() const;
			const ElsaType* get_type() const;
			Expression* get_expression() const;
			void set_expression(std::unique_ptr<Expression> expression);
			Expression* release_expression();
			std::unique_ptr<Expression> move_expression();

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring name_;
			std::unique_ptr<ElsaType> type_;
			std::unique_ptr<Expression> expression_;
		};
	}
}
