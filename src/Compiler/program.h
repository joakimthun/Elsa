#pragma once

#include <vector>
#include <memory>
#include <utility>

#include "exceptions\parsing_exception.h"
#include "ast\expression.h"

namespace elsa {
	namespace compiler {

		class Program
		{
		public:
			void add_statement(std::unique_ptr<Expression> node);
			void add_statement_front(std::unique_ptr<Expression> node);
			std::vector<std::unique_ptr<Expression>>& get_statements();

			template<typename TStatement>
			std::vector<TStatement*> get_statements_of_type()
			{
				auto statements = std::vector<TStatement*>();

				for (auto& statement : statements_)
				{
					if (auto s = dynamic_cast<TStatement*>(statement.get()))
					{
						statements.push_back(s);
					}
				}

				return statements;
			}

		private:
			std::vector<std::unique_ptr<Expression>> statements_;
		};
	}
}
