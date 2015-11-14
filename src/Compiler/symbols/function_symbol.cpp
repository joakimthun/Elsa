#include "function_symbol.h"

namespace elsa {
	namespace compiler {

		FunctionSymbol::FunctionSymbol(const FuncDeclarationExpression* expression)
			:
			expression_(expression)
		{}

		const FuncDeclarationExpression* FunctionSymbol::get_expression() const
		{
			return expression_;
		}
	}
}
