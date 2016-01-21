#include "vm_program.h"
#include "vm_program.h"
#include "vm_program.h"
#include "vm_program.h"
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

	void VMProgram::emit(std::size_t index, int instruction)
	{
		instructions_[index] = instruction;
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

	std::size_t VMProgram::mark_index()
	{
		instructions_.push_back(0);
		return instructions_.size() - 1;
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

	void VMProgram::add_func(std::unique_ptr<FunctionInfo> entry)
	{
		auto result = functions_.insert(std::pair<std::size_t, std::unique_ptr<FunctionInfo>>(entry->get_addr(), std::move(entry)));
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

	const FunctionInfo * VMProgram::get_func(const std::wstring& name) const
	{
		for (auto& entry : functions_)
		{
			if (entry.second->get_name() == name)
				return entry.second.get();
		}

		return nullptr;
	}

	const FunctionInfo * VMProgram::get_main() const
	{
		return get_func(entry_point_);
	}
	
	std::size_t VMProgram::add_struct(std::unique_ptr<StructInfo> entry)
	{
		structs_.push_back(std::move(entry));
		auto index = structs_.size() - 1;
		structs_.back()->set_index(index);
		return index;
	}
	
	const StructInfo* VMProgram::get_struct(std::size_t index) const
	{
		return structs_[index].get();
	}

	const StructInfo * VMProgram::get_struct(const std::wstring& name) const
	{
		for (auto& struct_entry : structs_)
		{
			if (struct_entry->get_name() == name)
				return struct_entry.get();
		}

		return nullptr;
	}
	
	std::size_t VMProgram::add_float(std::unique_ptr<FloatInfo> entry)
	{
		floats_.push_back(std::move(entry));
		return floats_.size() - 1;
	}
	
	const FloatInfo* VMProgram::get_float(std::size_t index) const
	{
		return floats_[index].get();
	}
	
	std::size_t VMProgram::add_char(std::unique_ptr<CharInfo> entry)
	{
		for (std::size_t i = 0; i < chars_.size(); i++)
		{
			if (chars_[i]->get_value() == entry->get_value())
				return i;
		}

		chars_.push_back(std::move(entry));
		return chars_.size() - 1;
	}
	
	const CharInfo* VMProgram::get_char_at(std::size_t index) const
	{
		return chars_[index].get();
	}
	
	std::size_t VMProgram::add_string(std::unique_ptr<StringInfo> entry)
	{
		strings_.push_back(std::move(entry));
		return strings_.size() - 1;
	}
	
	const StringInfo* VMProgram::get_string(std::size_t index) const
	{
		return strings_[index].get();
	}

}
