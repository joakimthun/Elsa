#pragma once

#include <cstddef>
#include <string>

#include "constant_entry.h"

namespace elsa {
	namespace vm {

		enum FunctionType
		{
			Static,
			Member
		};

		class FunctionEntry : public ConstantEntry
		{
		public:
			FunctionEntry(std::string name, std::size_t num_args, std::size_t num_locals, std::size_t addr, FunctionType type);
			~FunctionEntry();

			std::string get_name();
			std::size_t get_num_args();
			std::size_t get_num_locals();
			std::size_t get_addr();
			FunctionType get_type();

		private:
			std::string name_;
			std::size_t num_args_;
			std::size_t num_locals_;
			std::size_t addr_;
			FunctionType type_;
		};

	}
}
