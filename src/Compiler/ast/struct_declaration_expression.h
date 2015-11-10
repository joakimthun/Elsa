#pragma once

#include <string>
#include <vector>
#include <memory>

#include "expression.h"
#include "exceptions\elsa_exception.h"
#include "field_expression.h"

namespace elsa {
	namespace compiler {

		class StructDeclarationExpression : public Expression
		{
		public:
			void set_name(const std::wstring& name);
			void add_field_expression(std::unique_ptr<FieldExpression> expression);

			const std::wstring& get_name() const;
			const std::vector<std::unique_ptr<FieldExpression>>& get_fields() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring name_;
			std::vector<std::unique_ptr<FieldExpression>> fields_;
		};
	}
}
