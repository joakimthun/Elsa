#include "function_symbol.h"

namespace elsa {
	namespace compiler {

		FunctionSymbol::FunctionSymbol(const std::wstring& name)
			:
			name_(name)
		{}

		const std::wstring& FunctionSymbol::get_name() const
		{
			return name_;
		}

		LocalTable& FunctionSymbol::locals()
		{
			return locals_;
		}
	}
}
