#pragma once

#include <memory>
#include <utility>

#include "expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class ReturnExpression : public Expression
		{
		public:
			Expression* get_expression() const;
			ElsaType* get_type() const;

			void set_expression(std::unique_ptr<Expression> expression);
			void set_type(ElsaType* type);

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::unique_ptr<Expression> expression_;
			std::unique_ptr<ElsaType> type_;
		};

	}
}

