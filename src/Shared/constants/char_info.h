#pragma once

namespace elsa {

		class CharInfo
		{
		public:
			CharInfo(wchar_t value);

			wchar_t get_value() const;

		private:
			wchar_t value_;
		};

}
