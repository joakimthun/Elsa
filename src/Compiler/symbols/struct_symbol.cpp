#include "struct_symbol.h"

namespace elsa {
	namespace compiler {

		StructSymbol::StructSymbol(const std::wstring& name)
			: 
		name_(name)
		{}

		const std::wstring& StructSymbol::get_name() const
		{
			return name_;
		}

	}
}
