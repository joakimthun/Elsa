#include "native_function_info.h"

namespace elsa {
	namespace compiler {

		NativeFunctionInfo::NativeFunctionInfo(const std::wstring& name, std::size_t index)
			:
			name_(name),
			index_(index)
		{}
		
		const std::wstring& NativeFunctionInfo::get_name() const
		{
			return name_;
		}

		std::size_t NativeFunctionInfo::get_index() const
		{
			return index_;
		}

	}
}

