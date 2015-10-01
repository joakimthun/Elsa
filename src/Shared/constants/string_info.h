#pragma once

#include <string>

namespace elsa {

		class StringInfo
		{
		public:
			StringInfo(const std::wstring& value);

			std::wstring get_value() const;

		private:
			std::wstring value_;
		};

}
