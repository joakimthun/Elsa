#include "local_table.h"

namespace elsa {
	namespace compiler {

		LocalTable::LocalTable()
			:
			num_args_(0),
			num_locals_(0),
			nesting_(0)
		{
		}

		void LocalTable::push_new_scope()
		{
			local_table_.push_back(std::make_unique<LocalTable>());
			nesting_++;
		}

		void LocalTable::pop_current_scope()
		{
			if (nesting_ == 0)
				throw ParsingException("Pop can not be called on an empty symbol table stack");

			nesting_--;
		}

		void LocalTable::push_current_scope(const std::wstring& name, const ElsaType& type)
		{
			if (local_table_.size() == 0)
				throw ParsingException("Push can not be called on an empty symbol table stack");

			auto& current_table = local_table_.back();

			local_table_[nesting_]->add(name, new LocalSymbol(name, num_args_ + num_locals_, type));
		}

		bool LocalTable::current_scope_has_entry(const std::wstring& name)
		{
			if (local_table_.size() == 0)
				throw ParsingException("The symbol table stack is empty");

			return local_table_[nesting_]->has_entry(name);
		}

		const LocalSymbol* LocalTable::get_local(const std::wstring& name) const
		{
			for (auto& it = local_table_.rbegin(); it != local_table_.rend(); ++it)
			{
				auto local = it->get()->get(name);
				if (local != nullptr)
					return local;
			}

			throw ParsingException("Tried to access an undefined local variable");
		}

		bool LocalTable::scope_has_entry(std::size_t nesting, const std::wstring& name)
		{
			if (nesting > local_table_.size() - 1)
				throw ParsingException("The symbol table does not contain that many scopes");

			return local_table_[nesting]->has_entry(name);
		}

		const LocalSymbol* LocalTable::get_local(std::size_t nesting, const std::wstring& name) const
		{
			if (nesting > local_table_.size() - 1)
				throw ParsingException("The symbol table does not contain that many scopes");
			
			return local_table_[nesting]->get(name);
		}

		void LocalTable::increment_num_args()
		{
			num_args_++;
		}

		void LocalTable::increment_num_locals()
		{
			num_locals_++;
		}

		void LocalTable::reset_num_locals_and_num_args()
		{
			num_args_ = 0;
			num_locals_ = 0;
		}

	}
}
