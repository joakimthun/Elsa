#include "function_entry.h"

namespace elsa {
	namespace vm {

		FunctionEntry::FunctionEntry(std::string name, std::size_t num_args, std::size_t num_locals, std::size_t addr, FunctionType type)
			:
			name_(name),
			num_args_(num_args),
			num_locals_(num_locals),
			addr_(addr),
			type_(type)
		{}

		FunctionEntry::~FunctionEntry() {}

		std::string FunctionEntry::get_name() const
		{
			return name_;
		}

		std::size_t FunctionEntry::get_num_args() const
		{
			return num_args_;
		}

		std::size_t FunctionEntry::get_num_locals() const
		{
			return num_locals_;
		}

		std::size_t FunctionEntry::get_addr() const
		{
			return addr_;
		}

		FunctionType FunctionEntry::get_type() const
		{
			return type_;
		}

	}
}