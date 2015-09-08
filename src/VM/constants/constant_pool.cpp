#include "constant_pool.h"

namespace elsa {
	namespace vm {

		ConstantPool::ConstantPool() {}
		ConstantPool::~ConstantPool() {}

		void ConstantPool::add_entry(ConstantEntry* entry) 
		{
			entries_.push_back(std::unique_ptr<ConstantEntry>(entry));
		}

		FunctionEntry* ConstantPool::get_func_at(std::size_t addr)
		{
			for (std::size_t i = 0; i < entries_.size(); ++i) 
			{
				auto e = (FunctionEntry*)entries_[i].get();
				if (e->get_addr() == addr)
					return e;
			}

			throw;
		}

	}
}
