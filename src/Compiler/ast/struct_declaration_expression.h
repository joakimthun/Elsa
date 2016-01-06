#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "expression.h"
#include "..\exceptions\parsing_exception.h"
#include "field_expression.h"
#include "func_declaration_expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class ElsaParser;

		class StructDeclarationExpression : public Expression
		{
		public:
			StructDeclarationExpression();
			StructDeclarationExpression(bool is_generic);

			const StructDeclarationExpression* create_generic(std::unique_ptr<ElsaType> type, ElsaParser* parser) const;

			void set_name(const std::wstring& name);
			void add_field_expression(std::unique_ptr<FieldExpression> expression);
			void add_member_function(std::unique_ptr<FuncDeclarationExpression> expression);
			const FuncDeclarationExpression* get_member_function(const std::wstring& name) const;
			const ElsaType* get_generic_type() const;
			bool is_generic_type() const;

			const std::wstring& get_name(bool inherited = false) const;
			const std::vector<std::unique_ptr<FieldExpression>>& get_fields() const;
			const std::vector<std::unique_ptr<FuncDeclarationExpression>>& get_functions() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			const StructDeclarationExpression* parent_;
			std::unique_ptr<ElsaType> generic_type_;
			bool is_generic_;
			std::wstring name_;
			std::vector<std::unique_ptr<FieldExpression>> fields_;
			std::vector<std::unique_ptr<FuncDeclarationExpression>> functions_;
		};
	}
}
