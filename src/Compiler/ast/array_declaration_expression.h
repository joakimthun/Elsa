#pragma once

#include <memory>
#include <utility>

#include "expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class ArrayDeclarationExpression : public Expression
		{
		public:
			void set_type(ElsaType* type);
			const ElsaType* get_type() const;

			void set_size_expression(std::unique_ptr<Expression> size_expression);
			Expression* get_size_expression();

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::unique_ptr<ElsaType> type_;
			std::unique_ptr<Expression> size_expression_;
		};
	}
}