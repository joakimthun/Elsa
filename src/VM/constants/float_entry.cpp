#include "float_entry.h"

namespace elsa {
	namespace vm {

		FloatEntry::FloatEntry(float value) 
			:
			value_(value)
		{
		}

		float FloatEntry::get_value() const
		{
			return value_;
		}

	}
}
