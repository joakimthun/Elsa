#include "constant_pool.h"

namespace elsa {
	namespace vm {

		void ConstantPool::add_func(FunctionInfo* entry) 
		{
			auto result = functions_.insert(std::pair<std::size_t, std::unique_ptr<FunctionInfo>>(entry->get_addr(), std::unique_ptr<FunctionInfo>(entry)));
			if (!result.second)
			{
				throw ElsaException("A function is already specified at that address");
			}
		}

		const FunctionInfo* ConstantPool::get_func(std::size_t addr) const
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

		void ConstantPool::add_struct(StructInfo* entry)
		{
			structs_.push_back(std::unique_ptr<StructInfo>(entry));
		}

		const StructInfo* ConstantPool::get_struct(std::size_t index) const
		{
			return structs_[index].get();
		}

		void ConstantPool::add_float(FloatInfo* entry)
		{
			floats_.push_back(std::unique_ptr<FloatInfo>(entry));
		}

		const FloatInfo* ConstantPool::get_float(std::size_t index) const
		{
			return floats_[index].get();
		}

		void ConstantPool::add_char(CharInfo* entry) 
		{
			chars_.push_back(std::unique_ptr<CharInfo>(entry));
		}

		const CharInfo* ConstantPool::get_char_at(std::size_t index) const
		{
			return chars_[index].get();
		}

		void ConstantPool::add_string(StringInfo* entry)
		{
			strings_.push_back(std::unique_ptr<StringInfo>(entry));
		}

		const StringInfo* ConstantPool::get_string(std::size_t index) const
		{
			return strings_[index].get();
		}

	}
}
