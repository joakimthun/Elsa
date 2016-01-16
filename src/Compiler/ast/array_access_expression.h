#pragma once

#include <memory>
#include <utility>
#include <cstddef>
#include <string>

#include "identifier_expression.h"
#include "struct_access_expression.h"
#include "typed_expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class ArrayAccessExpression : public Expression, public TypedExpression
		{
		public:
			void set_identifier_expression(std::unique_ptr<IdentifierExpression> identifier_expression);
			void set_index_expression(std::unique_ptr<Expression> expression);
			void set_struct_access_expression(StructAccessExpression* expression);

			IdentifierExpression* get_identifier_expression() const;
			Expression* get_index_expression() const;
			StructAccessExpression* get_struct_access_expression() const;

			const std::wstring& get_name() const override;
			const ElsaType* get_type() const override;
			ExpressionType get_expression_type() const override;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::unique_ptr<IdentifierExpression> identifier_expression_;
			std::unique_ptr<Expression> index_expression_;
			std::unique_ptr<StructAccessExpression> struct_access_expression_;
		};
	}
}