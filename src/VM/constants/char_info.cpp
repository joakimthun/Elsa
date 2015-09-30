#include "char_info.h"

namespace elsa {
	namespace vm {

		CharInfo::CharInfo(wchar_t value)
			:
			value_(value)
		{}

		wchar_t CharInfo::get_value() const
		{
			return value_;
		}
	}
}

