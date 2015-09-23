#pragma once

#include "constant_entry.h"

namespace elsa {
	namespace vm {

		class CharEntry : public ConstantEntry
		{
		public:
			CharEntry(wchar_t value);

			wchar_t get_value() const;

		private:
			wchar_t value_;
		};

	}
}
