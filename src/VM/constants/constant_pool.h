#pragma once

#include <memory>
#include <vector>
#include <cstddef>
#include <map>
#include <stdexcept>

#include "../exceptions/elsa_exception.h"
#include "function_info.h"
#include "struct_info.h"
#include "float_info.h"
#include "char_info.h"
#include "string_info.h"

namespace elsa {
	namespace vm {

		class ConstantPool
		{
		public:

			void add_func(FunctionInfo* entry);
			const FunctionInfo* get_func(std::size_t addr) const;

			void add_struct(StructInfo* entry);
			const StructInfo* get_struct(std::size_t index) const;

			void add_float(FloatInfo* entry);
			const FloatInfo* get_float(std::size_t index) const;

			void add_char(CharInfo* entry);
			const CharInfo* get_char_at(std::size_t index) const;

			void add_string(StringInfo* entry);
			const StringInfo* get_string(std::size_t index) const;

		private:
			std::map<std::size_t, std::unique_ptr<FunctionInfo>> functions_;
			std::vector<std::unique_ptr<StructInfo>> structs_;
			std::vector<std::unique_ptr<FloatInfo>> floats_;
			std::vector<std::unique_ptr<CharInfo>> chars_;
			std::vector<std::unique_ptr<StringInfo>> strings_;
		};

	}
}
