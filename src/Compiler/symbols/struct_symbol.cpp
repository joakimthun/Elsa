#include "struct_symbol.h"

namespace elsa {
	namespace compiler {

		StructSymbol::StructSymbol(const std::wstring& name, std::size_t index)
			: 
		name_(name),
		index_(index)
		{}
		
		const std::wstring& StructSymbol::get_name() const
		{
			return name_;
		}

		std::size_t StructSymbol::get_index() const
		{
			return index_;
		}

	}
}
