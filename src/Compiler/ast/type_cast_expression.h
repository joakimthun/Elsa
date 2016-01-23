#pragma once

#include <string>
#include <memory>

#include "expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class TypeCastExpression : public Expression
		{
		public:
			void set_dest_type(ElsaType* type);
			ElsaType* get_dest_type();

			void set_expression(std::unique_ptr<Expression> expression);
			Expression* get_expression();

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::unique_ptr<Expression> expression_;
			std::unique_ptr<ElsaType> dest_type_;
		};

	}
}
