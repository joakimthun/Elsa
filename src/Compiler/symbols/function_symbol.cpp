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

		bool FunctionSymbol::has_local(const std::wstring& name)
		{
			return locals_.has_entry(name);
		}

		LocalSymbol* FunctionSymbol::get_local(const std::wstring& name)
		{
			return locals_.get(name);
		}
	}
}
