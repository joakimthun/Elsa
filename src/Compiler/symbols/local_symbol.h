#pragma once

#include <string>
#include <cstddef>

namespace elsa {
	namespace compiler {

		class LocalSymbol
		{
		public:
			LocalSymbol(const std::wstring& name, std::size_t index);

		private:
			std::wstring name_;
			std::size_t index_;
		};

	}
}
