#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <memory>

#include "..\object_types\otype.h"
#include "field_info.h"
#include "../exceptions/runtime_exception.h"

namespace elsa {

		class StructInfo
		{
		public:
			StructInfo(const std::string& name);
			~StructInfo();

			std::string get_name() const;
			std::size_t get_size() const;
			FieldInfo* get_field(std::size_t index) const;
			const std::vector<std::unique_ptr<FieldInfo>>& get_fields() const;

			void add_field(FieldInfo* field);

		private:
			void update_size(const FieldInfo& field);

			std::string name_;
			std::vector<std::unique_ptr<FieldInfo>> fields_;
			std::size_t size_;
		};

}