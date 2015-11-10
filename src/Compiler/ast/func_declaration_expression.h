#pragma once

#include <string>
#include <vector>
#include <memory>

#include "expression.h"
#include "argument_expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class FuncDeclarationExpression : public Expression
		{
		public:
			void add_args_expression(std::unique_ptr<ArgumentExpression> expression);
			void add_body_expression(std::unique_ptr<Expression> expression);

			void set_name(const std::wstring& name);
			void set_return_type(ElsaType* return_type);

			const std::wstring& get_name() const;
			const ElsaType* get_return_type() const;
			const std::vector<std::unique_ptr<Expression>>& get_body() const;
			const std::vector<std::unique_ptr<ArgumentExpression>>& get_args() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring name_;
			std::unique_ptr<ElsaType> return_type_;
			std::vector<std::unique_ptr<ArgumentExpression>> args_;
			std::vector<std::unique_ptr<Expression>> body_;
		};
	}
}
