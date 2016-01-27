#pragma once

#include <memory>
#include <utility>

#include "expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class FieldInitializerExpression : public Expression
		{
		public:
			FieldInitializerExpression(std::unique_ptr<Expression> exp, std::size_t index);

			void add_value(std::unique_ptr<Expression> exp);
			Expression* get_value();

			void set_index(std::size_t index);
			std::size_t get_index() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::size_t index_;
			std::unique_ptr<Expression> value_;
		};
	}
}