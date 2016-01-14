#pragma once

#include <cstddef>
#include <vector>
#include <string>
#include <memory>

#include "../types/elsa_type.h"
namespace elsa {
	namespace compiler {

		class NativeFunctionInfo
		{
		public:
			NativeFunctionInfo(const std::wstring& name, ObjectType return_type, std::size_t index);

			void add_arg(ElsaType* type);
			ObjectType get_return_type();
			const std::wstring& get_name() const;
			std::size_t num_args() const;
			std::size_t get_index() const;
			const std::vector<std::unique_ptr<ElsaType>>& get_args() const;

		private:
			std::vector<std::unique_ptr<ElsaType>> args_;
			ObjectType return_type_;
			std::wstring name_;
			std::size_t index_;
		};

	}
}
