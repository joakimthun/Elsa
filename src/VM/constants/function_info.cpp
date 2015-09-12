#include "function_info.h"

namespace elsa {
	namespace vm {

		FunctionInfo::FunctionInfo(const std::string& name, std::size_t num_args, std::size_t num_locals, std::size_t addr, FunctionType type)
			:
			name_(name),
			num_args_(num_args),
			num_locals_(num_locals),
			addr_(addr),
			type_(type)
		{}

		FunctionInfo::~FunctionInfo() {}

		std::string FunctionInfo::get_name() const
		{
			return name_;
		}

		std::size_t FunctionInfo::get_num_args() const
		{
			return num_args_;
		}

		std::size_t FunctionInfo::get_num_locals() const
		{
			return num_locals_;
		}

		std::size_t FunctionInfo::get_addr() const
		{
			return addr_;
		}

		FunctionType FunctionInfo::get_type() const
		{
			return type_;
		}

	}
}