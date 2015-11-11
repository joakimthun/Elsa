#pragma once

#include <string>
#include <cstddef>

#include "../types/elsa_type.h"
#include "../ast/struct_declaration_expression.h"

namespace elsa {
	namespace compiler {

		class LocalSymbol
		{
		public:
			LocalSymbol(const std::wstring& name, std::size_t index, const ElsaType& type);
			LocalSymbol::LocalSymbol(const std::wstring& name, std::size_t index, const ElsaType& type, const StructDeclarationExpression* struct_expression);

			const std::wstring& get_name() const;
			std::size_t get_index() const;
			const ElsaType& get_type() const;
			const StructDeclarationExpression* get_struct_expression() const;

		private:
			std::wstring name_;
			std::size_t index_;
			ElsaType type_;
			const StructDeclarationExpression* struct_expression_;
		};

	}
}
