#pragma once

#include <memory>
#include <utility>

#include "expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class ArrayInitializerListExpression : public Expression
		{
		public:
			void set_type(ElsaType* type);
			const ElsaType* get_type() const;

			void add_value(std::unique_ptr<Expression> exp);
			const std::vector<std::unique_ptr<Expression>>& get_values() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::unique_ptr<ElsaType> type_;
			std::vector<std::unique_ptr<Expression>> values_;
		};
	}
}