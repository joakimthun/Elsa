#pragma once

#include <memory>
#include <vector>

#include "identifier_expression.h"
#include "../token.h"
#include "../types/elsa_type.h"
#include "exceptions\parsing_exception.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class FieldAccessExpression : public Expression
		{
		public:
			void add_expression(std::unique_ptr<IdentifierExpression> expression);
			const std::vector<std::unique_ptr<IdentifierExpression>>& get_expressions() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::vector<std::unique_ptr<IdentifierExpression>> expressions_;
		};
	}
}