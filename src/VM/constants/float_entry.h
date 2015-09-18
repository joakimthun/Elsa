#pragma once

#include "constant_entry.h"

namespace elsa {
	namespace vm {

		class FloatEntry : public ConstantEntry
		{
		public:
			FloatEntry(float value);

			float get_value() const;

		private:
			float value_;
		};

	}
}
