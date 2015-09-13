#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <memory>

#include "../exceptions/elsa_exception.h"
#include "../exceptions/runtime_exception.h"
#include "../types/otype.h"
#include "constant_entry.h"
#include "field_info.h"

namespace elsa {
	namespace vm {

		class StructInfo : public ConstantEntry
		{
		public:
			StructInfo(const std::string& name);
			~StructInfo();

			std::string get_name() const;
			std::size_t get_size() const;
			FieldInfo* get_field(std::size_t index) const;

			void add_field(FieldInfo* field);

		private:
			void update_size(const FieldInfo& field);

			std::string name_;
			std::vector<std::unique_ptr<FieldInfo>> fields_;
			std::size_t size_;
		};

	}
}
