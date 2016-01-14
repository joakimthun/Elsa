#pragma once

#include <cstddef>
#include <vector>
#include <string>
#include <memory>

#include "../types/elsa_type.h"
namespace elsa {
	namespace compiler {

		class NativeFunctionInfo
		{
		public:
			NativeFunctionInfo(const std::wstring& name, std::size_t index);

			const std::wstring& get_name() const;
			std::size_t get_index() const;

		private:
			std::wstring name_;
			std::size_t index_;
		};

	}
}
