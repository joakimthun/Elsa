#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "../exceptions/elsa_exception.h"
#include "../types/object.h"
#include "constant_entry.h"

namespace elsa {
	namespace vm {

		struct FieldInfo
		{
			std::size_t size;
			OType type;
		};

		class StructInfo : public ConstantEntry
		{
		public:
			StructInfo(const std::string& name);
			~StructInfo();

			std::string get_name() const;
			std::size_t get_size() const;
			void add_field(FieldInfo field);

		private:
			void update_size(const FieldInfo& field);

			std::string name_;
			std::vector<FieldInfo> fields_;
			std::size_t size_;
		};

	}
}
