#include "native_function_info.h"

namespace elsa {
	namespace compiler {

		NativeFunctionInfo::NativeFunctionInfo(const std::wstring& name, ObjectType return_type, std::size_t index)
			:
			name_(name),
			return_type_(return_type),
			index_(index)
		{}
		
		void NativeFunctionInfo::add_arg(ElsaType* type)
		{
			args_.push_back(std::unique_ptr<ElsaType>(type));
		}
		
		ObjectType NativeFunctionInfo::get_return_type()
		{
			return return_type_;
		}
		
		const std::wstring& NativeFunctionInfo::get_name() const
		{
			return name_;
		}

		std::size_t NativeFunctionInfo::num_args() const
		{
			return args_.size();
		}

		std::size_t NativeFunctionInfo::get_index() const
		{
			return index_;
		}

		const std::vector<std::unique_ptr<ElsaType>>& NativeFunctionInfo::get_args() const
		{
			return args_;
		}

	}
}

