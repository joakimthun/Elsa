#pragma once

#include <memory>
#include <utility>

#include "field_initializer_expression.h"
#include "create_struct_expression.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class StructInitializerListExpression : public Expression
		{
		public:
			void set_create_struct_expression(std::unique_ptr<CreateStructExpression> exp);
			const CreateStructExpression* get_create_struct_expression() const;

			void add_value_expression(std::unique_ptr<FieldInitializerExpression> exp);
			std::vector<std::unique_ptr<FieldInitializerExpression>>& get_value_expressions();

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::unique_ptr<CreateStructExpression> create_struct_expression_;
			std::vector<std::unique_ptr<FieldInitializerExpression>> values_;
		};
	}
}