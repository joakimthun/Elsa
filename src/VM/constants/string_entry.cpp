#include "string_entry.h"

namespace elsa {
	namespace vm {

		StringEntry::StringEntry(const std::wstring& value) 
			:
			value_(value)
		{}

		std::wstring StringEntry::get_value() const
		{
			return value_;
		}

	}
}

