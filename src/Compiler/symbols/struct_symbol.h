#pragma once

#include <string>
#include <cstddef>

#include "../ast/struct_declaration_expression.h"

namespace elsa {
	namespace compiler {

		class StructSymbol
		{
		public:
			StructSymbol(const std::wstring& name, StructDeclarationExpression* expression);

			const std::wstring& get_name() const;
			const StructDeclarationExpression* get_expression() const;

		private:
			std::wstring name_;
			StructDeclarationExpression* expression_;
		};

	}
}
