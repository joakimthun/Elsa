#pragma once

#include <memory>
#include <vector>
#include <cstddef>
#include <map>
#include <stdexcept>

#include "opcodes\opcodes.h"
#include "constants\char_info.h"
#include "constants\float_info.h"
#include "constants\function_info.h"
#include "constants\string_info.h"
#include "constants\struct_info.h"

namespace elsa {

	class VMProgram
	{
	public:
		VMProgram();

		void emit(OpCode instruction);
		void emit(int instruction);
		void emit(const std::vector<int>& instructions);
		std::size_t get_next_instruction_index();
		std::vector<int>& get_instructions();

		void set_entry_point(int entry_point);
		int get_entry_point();

		void add_func(FunctionInfo* entry);
		const FunctionInfo* get_func(std::size_t addr) const;
		const FunctionInfo* get_main() const;

		std::size_t add_struct(StructInfo* entry);
		const StructInfo* get_struct(std::size_t index) const;

		std::size_t add_float(FloatInfo* entry);
		const FloatInfo* get_float(std::size_t index) const;

		std::size_t add_char(CharInfo* entry);
		const CharInfo* get_char_at(std::size_t index) const;

		std::size_t add_string(StringInfo* entry);
		const StringInfo* get_string(std::size_t index) const;

	private:
		std::vector<int> instructions_;
		int entry_point_;
		std::map<std::size_t, std::unique_ptr<FunctionInfo>> functions_;
		std::vector<std::unique_ptr<StructInfo>> structs_;
		std::vector<std::unique_ptr<FloatInfo>> floats_;
		std::vector<std::unique_ptr<CharInfo>> chars_;
		std::vector<std::unique_ptr<StringInfo>> strings_;
	};

}
