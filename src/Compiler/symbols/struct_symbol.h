#pragma once

#include <string>
#include <cstddef>

namespace elsa {
	namespace compiler {

		class StructSymbol
		{
		public:
			StructSymbol(const std::wstring& name, std::size_t index);

			const std::wstring& get_name() const;
			std::size_t get_index() const;

		private:
			std::wstring name_;
			std::size_t index_;
		};

	}
}
