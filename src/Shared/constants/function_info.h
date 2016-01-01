#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "../opcodes/opcodes.h"

namespace elsa {

		enum FunctionType
		{
			Static,
			Member
		};

		class FunctionInfo
		{
		public:
			FunctionInfo(const std::wstring& name, std::size_t num_args, std::size_t num_locals, std::size_t addr, FunctionType type, bool builtin = false);
			FunctionInfo(const std::wstring& name);
			~FunctionInfo();

			std::wstring get_name() const;
			std::size_t get_num_args() const;
			void set_num_args(std::size_t num_args);
			std::size_t get_num_locals() const;
			void set_num_locals(std::size_t num_locals);
			std::size_t get_addr() const;
			void set_addr(std::size_t addr);
			FunctionType get_type() const;
			bool is_builtin() const;

		private:
			std::wstring name_;
			std::size_t num_args_;
			std::size_t num_locals_;
			std::size_t addr_;
			FunctionType type_;
			bool builtin_;
		};

}
