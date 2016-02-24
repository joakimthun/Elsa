#pragma once

#include <string>
#include <memory>
#include <utility>

#include "expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class GroupedExpression : public Expression
		{
		public:
			const ElsaType* get_type() const;
			void set_type(ElsaType* type);

			Expression* get_expression();
			void set_expression(std::unique_ptr<Expression> exp);

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::unique_ptr<Expression> expression_;
			std::unique_ptr<ElsaType> type_;
		};

	}
}
