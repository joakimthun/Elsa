#pragma once

#include <cstddef>
#include <vector>
#include <string>
#include <memory>

#include "object_types\otype.h"

namespace elsa {
	namespace compiler {

		struct NativeFunctionArgument
		{
			std::vector<OType> valid_types;
		};

		class NativeFunctionInfo
		{
		public:
			NativeFunctionInfo(const std::wstring& name, OType return_type, std::size_t index);

			void add_arg();
			void add_arg_type(std::size_t index, OType type);
			OType get_return_type();
			const std::wstring& get_name() const;
			bool is_valid_arg_type(std::size_t index, OType type);
			std::size_t num_args() const;
			std::size_t get_index() const;

		private:
			std::vector<std::unique_ptr<NativeFunctionArgument>> args_;
			OType return_type_;
			std::wstring name_;
			std::size_t index_;
		};

	}
}
