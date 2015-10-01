#include "char_info.h"

namespace elsa {

		CharInfo::CharInfo(wchar_t value)
			:
			value_(value)
		{}

		wchar_t CharInfo::get_value() const
		{
			return value_;
		}
}

