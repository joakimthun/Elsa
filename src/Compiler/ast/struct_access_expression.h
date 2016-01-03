#pragma once

#include <memory>
#include <vector>

#include "identifier_expression.h"
#include "typed_expression.h"
#include "../token.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class StructAccessExpression : public Expression
		{
		public:
			void set_base(std::unique_ptr<IdentifierExpression> expression);
			void add_expression(TypedExpression* expression);

			IdentifierExpression* get_base();
			const std::vector<std::unique_ptr<TypedExpression>>& get_expressions() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::unique_ptr<IdentifierExpression> base_;
			std::vector<std::unique_ptr<TypedExpression>> expressions_;
		};
	}
}