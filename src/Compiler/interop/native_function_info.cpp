#include "native_function_info.h"

namespace elsa {
	namespace compiler {

		NativeFunctionInfo::NativeFunctionInfo(const std::wstring& name, ObjectType return_type, std::size_t index)
			:
			name_(name),
			return_type_(return_type),
			index_(index)
		{}
		
		void NativeFunctionInfo::add_arg()
		{
			args_.push_back(std::make_unique<NativeFunctionArgument>());
		}

		void NativeFunctionInfo::add_arg_type(std::size_t index, ObjectType type)
		{
			args_[index]->valid_types.push_back(type);
		}
		
		ObjectType NativeFunctionInfo::get_return_type()
		{
			return return_type_;
		}
		
		const std::wstring& NativeFunctionInfo::get_name() const
		{
			return name_;
		}

		bool NativeFunctionInfo::is_valid_arg_type(std::size_t index, ObjectType type)
		{
			for (const auto& arg_type : args_[index]->valid_types)
			{
				if (arg_type == type)
					return true;
			}

			return false;
		}

		std::size_t NativeFunctionInfo::num_args() const
		{
			return args_.size();
		}

		std::size_t NativeFunctionInfo::get_index() const
		{
			return index_;
		}

	}
}

