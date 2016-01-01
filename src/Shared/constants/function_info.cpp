#include "function_info.h"
#include "function_info.h"
#include "function_info.h"
#include "function_info.h"
#include "function_info.h"

namespace elsa {

		FunctionInfo::FunctionInfo(const std::wstring& name, std::size_t num_args, std::size_t num_locals, std::size_t addr, FunctionType type, bool builtin)
			:
			name_(name),
			num_args_(num_args),
			num_locals_(num_locals),
			addr_(addr),
			type_(type),
			builtin_(builtin)
		{}

		FunctionInfo::FunctionInfo(const std::wstring& name)
			: 
			name_(name),
			num_args_(0),
			num_locals_(0),
			addr_(0),
			type_(FunctionType::Static),
			builtin_(false)
		{
		}

		FunctionInfo::~FunctionInfo() {}

		std::wstring FunctionInfo::get_name() const
		{
			return name_;
		}

		std::size_t FunctionInfo::get_num_args() const
		{
			return num_args_;
		}

		void FunctionInfo::set_num_args(std::size_t num_args)
		{
			num_args_ = num_args;
		}

		std::size_t FunctionInfo::get_num_locals() const
		{
			return num_locals_;
		}

		void FunctionInfo::set_num_locals(std::size_t num_locals)
		{
			num_locals_ = num_locals;
		}

		std::size_t FunctionInfo::get_addr() const
		{
			return addr_;
		}

		void FunctionInfo::set_addr(std::size_t addr)
		{
			addr_ = addr;
		}

		FunctionType FunctionInfo::get_type() const
		{
			return type_;
		}

		bool FunctionInfo::is_builtin() const
		{
			return builtin_;
		}

}