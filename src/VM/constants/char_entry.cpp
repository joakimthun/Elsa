#include "char_entry.h"

namespace elsa {
	namespace vm {

		CharEntry::CharEntry(wchar_t value)
			:
			value_(value)
		{}

		wchar_t CharEntry::get_value() const
		{
			return value_;
		}
	}
}

