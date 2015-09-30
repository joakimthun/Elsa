#pragma once

namespace elsa {
	namespace vm {

		class FloatInfo
		{
		public:
			FloatInfo(float value);

			float get_value() const;

		private:
			float value_;
		};

	}
}
