#include "local_symbol.h"

namespace elsa {
	namespace compiler {

		LocalSymbol::LocalSymbol(const std::wstring& name, std::size_t index)
			:
			name_(name),
			index_(index)
		{}

	}
}
