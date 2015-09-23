#pragma once

#include <string>

#include "constant_entry.h"

namespace elsa {
	namespace vm {

		class StringEntry : public ConstantEntry
		{
		public:
			StringEntry(const std::wstring& value);

			std::wstring get_value() const;

		private:
			std::wstring value_;
		};

	}
}
