#pragma once

#include <string>
#include <vector>
#include <memory>

#include "expression.h"
#include "exceptions\parsing_exception.h"
#include "field_expression.h"
#include "func_declaration_expression.h"

namespace elsa {
	namespace compiler {

		class StructDeclarationExpression : public Expression
		{
		public:
			void set_name(const std::wstring& name);
			void add_field_expression(std::unique_ptr<FieldExpression> expression);
			void add_member_function(std::unique_ptr<FuncDeclarationExpression> expression);
			const FuncDeclarationExpression* get_member_function(const std::wstring& name) const;

			const std::wstring& get_name() const;
			const std::vector<std::unique_ptr<FieldExpression>>& get_fields() const;
			const std::vector<std::unique_ptr<FuncDeclarationExpression>>& get_functions() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring name_;
			std::vector<std::unique_ptr<FieldExpression>> fields_;
			std::vector<std::unique_ptr<FuncDeclarationExpression>> functions_;
		};
	}
}
