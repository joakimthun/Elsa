#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <cstddef>
#include <map>
#include <stdexcept>
#include <string>

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
		void emit(std::size_t index, int instruction);
		void emit(int instruction);
		void emit(const std::vector<int>& instructions);
		std::size_t mark_index();
		std::size_t get_next_instruction_index();
		std::vector<int>& get_instructions();

		void set_entry_point(int entry_point);
		int get_entry_point();

		void add_func(std::unique_ptr<FunctionInfo> entry);
		const FunctionInfo* get_func(std::size_t addr) const;
		const FunctionInfo* get_func(const std::wstring& name) const;
		const FunctionInfo* get_main() const;

		std::size_t add_struct(std::unique_ptr<StructInfo> entry);
		const StructInfo* get_struct(std::size_t index) const;
		const StructInfo* get_struct(const std::wstring& name) const;

		std::size_t add_float(std::unique_ptr<FloatInfo> entry);
		const FloatInfo* get_float(std::size_t index) const;

		std::size_t add_char(std::unique_ptr<CharInfo> entry);
		const CharInfo* get_char_at(std::size_t index) const;

		std::size_t add_string(std::unique_ptr<StringInfo> entry);
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
