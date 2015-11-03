#include "vm_program.h"

namespace elsa {

	VMProgram::VMProgram()
		:
		entry_point_(-1)
	{}

	void VMProgram::emit(OpCode instruction)
	{
		instructions_.push_back(static_cast<int>(instruction));
	}

	void VMProgram::emit(int instruction)
	{
		instructions_.push_back(instruction);
	}

	void VMProgram::emit(const std::vector<int>& instructions)
	{
		for (auto inst : instructions)
		{
			emit(inst);
		}
	}

	std::size_t VMProgram::get_next_instruction_index()
	{
		return instructions_.size();
	}

	std::vector<int>& VMProgram::get_instructions()
	{
		return instructions_;
	}

	void VMProgram::set_entry_point(int entry_point)
	{
		entry_point_ = entry_point;
	}

	int VMProgram::get_entry_point()
	{
		return entry_point_;
	}

	void VMProgram::add_func(FunctionInfo* entry)
	{
		auto result = functions_.insert(std::pair<std::size_t, std::unique_ptr<FunctionInfo>>(entry->get_addr(), std::unique_ptr<FunctionInfo>(entry)));
		if (!result.second)
		{
			throw ElsaException("A function is already specified at that address");
		}
	}
	
	const FunctionInfo* VMProgram::get_func(std::size_t addr) const
	{
		try
		{
			return functions_.at(addr).get();
		}
		catch (std::out_of_range)
		{
			throw ElsaException("No function found at the specified address");
		}
	}

	const FunctionInfo * VMProgram::get_main() const
	{
		return get_func(entry_point_);
	}
	
	std::size_t VMProgram::add_struct(StructInfo* entry)
	{
		structs_.push_back(std::unique_ptr<StructInfo>(entry));
		return structs_.size() - 1;
	}
	
	const StructInfo* VMProgram::get_struct(std::size_t index) const
	{
		return structs_[index].get();
	}
	
	std::size_t VMProgram::add_float(FloatInfo* entry)
	{
		floats_.push_back(std::unique_ptr<FloatInfo>(entry));
		return floats_.size() - 1;
	}
	
	const FloatInfo* VMProgram::get_float(std::size_t index) const
	{
		return floats_[index].get();
	}
	
	std::size_t VMProgram::add_char(CharInfo* entry)
	{
		chars_.push_back(std::unique_ptr<CharInfo>(entry));
		return chars_.size() - 1;
	}
	
	const CharInfo* VMProgram::get_char_at(std::size_t index) const
	{
		return chars_[index].get();
	}
	
	std::size_t VMProgram::add_string(StringInfo* entry)
	{
		strings_.push_back(std::unique_ptr<StringInfo>(entry));
		return strings_.size() - 1;
	}
	
	const StringInfo* VMProgram::get_string(std::size_t index) const
	{
		return strings_[index].get();
	}

}
