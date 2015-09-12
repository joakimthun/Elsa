#pragma once

#include <cstddef>
#include <string>

#include "constant_entry.h"

namespace elsa {
	namespace vm {

		struct StructField
		{
			std::size_t i;

		};

		class StructInfo : public ConstantEntry
		{
		public:
			StructInfo(const std::string& name);
			~StructInfo();

			std::string get_name() const;
			std::size_t get_size() const;

		private:
			std::string name_;
		};

	}
}
