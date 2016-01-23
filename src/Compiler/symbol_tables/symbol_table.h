#pragma once

#include <unordered_map>
#include <memory>

namespace elsa {
	namespace compiler {

		template<typename TKey, typename TValue>
		class SymbolTable
		{
		public:
			bool has_entry(const TKey& key) const
			{
				auto it = table_.find(key);
				return it != table_.end();
			}

			TValue* get(const TKey& key)
			{
				auto it = table_.find(key);

				if (it == table_.end())
					return nullptr;

				return it->second.get();
			}

			void add(const TKey& key, TValue* value)
			{
				table_.insert(std::pair<TKey, std::unique_ptr<TValue>>(key, std::unique_ptr<TValue>(value)));
			}

		private:
			std::unordered_map<TKey, std::unique_ptr<TValue>> table_;
		};

	}
}
