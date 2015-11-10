#pragma once

#include <string>
#include <cstddef>

namespace elsa {
	namespace compiler {

		class StructSymbol
		{
		public:
			StructSymbol(const std::wstring& name);

			const std::wstring& get_name() const;

		private:
			std::wstring name_;
		};

	}
}
