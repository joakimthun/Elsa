#include "constant_pool.h"

namespace elsa {
	namespace vm {

		ConstantPool::ConstantPool() {}
		ConstantPool::~ConstantPool() {}

		void ConstantPool::add_entry(ConstantEntry* entry) 
		{
			entries_.push_back(std::unique_ptr<ConstantEntry>(entry));
		}

		FunctionInfo* ConstantPool::get_func_at(std::size_t addr)
		{
			for (std::size_t i = 0; i < entries_.size(); ++i)
			{
				auto e = static_cast<FunctionInfo*>(entries_[i].get());
				if (e->get_addr() == addr)
					return e;
			}

			throw ElsaException("No function found at the specified address");
		}

		StructInfo* ConstantPool::get_struct_at(std::size_t index)
		{
			return static_cast<StructInfo*>(entries_[index].get());
		}

		FloatEntry* ConstantPool::get_float_at(std::size_t index)
		{
			return static_cast<FloatEntry*>(entries_[index].get());
		}

		CharEntry* ConstantPool::get_char_at(std::size_t index)
		{
			return static_cast<CharEntry*>(entries_[index].get());
		}

	}
}
