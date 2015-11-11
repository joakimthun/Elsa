#include "struct_symbol.h"

namespace elsa {
	namespace compiler {

		StructSymbol::StructSymbol(const std::wstring& name, StructDeclarationExpression* expression)
			: 
		name_(name),
		expression_(expression)
		{}

		const std::wstring& StructSymbol::get_name() const
		{
			return name_;
		}

		const StructDeclarationExpression* StructSymbol::get_expression() const
		{
			return expression_;
		}

	}
}
