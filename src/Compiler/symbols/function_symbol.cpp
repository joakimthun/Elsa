#include "function_symbol.h"

namespace elsa {
	namespace compiler {

		FunctionSymbol::FunctionSymbol(const std::wstring& name)
			:
			name_(name),
			next_local_index_(0)
		{}

		const std::wstring& FunctionSymbol::get_name() const
		{
			return name_;
		}

		bool FunctionSymbol::has_local(const std::wstring& name) const
		{
			return locals_.has_entry(name);
		}

		void FunctionSymbol::add_local(const std::wstring& name, const ElsaType& type)
		{
			locals_.add(name, new LocalSymbol(name, next_local_index_++, type));
		}

		LocalSymbol* FunctionSymbol::get_local(const std::wstring& name)
		{
			return locals_.get(name);
		}
	}
}
