#include "string_info.h"

namespace elsa {
	namespace vm {

		StringInfo::StringInfo(const std::wstring& value)
			:
			value_(value)
		{}

		std::wstring StringInfo::get_value() const
		{
			return value_;
		}

	}
}

