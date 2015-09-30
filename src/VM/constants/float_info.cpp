#include "float_info.h"

namespace elsa {
	namespace vm {

		FloatInfo::FloatInfo(float value)
			:
			value_(value)
		{
		}

		float FloatInfo::get_value() const
		{
			return value_;
		}

	}
}
