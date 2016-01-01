#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "field_info.h"
#include "function_info.h"
#include "../exceptions/runtime_exception.h"
#include "../exceptions/codegen_exception.h"

namespace elsa {

		class StructInfo
		{
		public:
			StructInfo(const std::wstring& name);
			~StructInfo();

			std::wstring get_name() const;
			std::size_t get_size() const;
			FieldInfo* get_field(std::size_t index) const;
			FunctionInfo* get_function(std::wstring name) const;
			void set_index(std::size_t index);
			std::size_t get_index() const;
			const std::vector<std::unique_ptr<FieldInfo>>& get_fields() const;

			void add_field(std::unique_ptr<FieldInfo> field);
			void add_function(std::unique_ptr<FunctionInfo> function);

		private:
			void update_size(const FieldInfo& field);

			std::wstring name_;
			std::vector<std::unique_ptr<FieldInfo>> fields_;
			std::vector<std::unique_ptr<FunctionInfo>> functions_;
			std::size_t size_;
			std::size_t index_;

		};

}
