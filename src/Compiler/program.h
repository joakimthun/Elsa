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

		private:
			std::vector<std::unique_ptr<Expression>> statements_;
		};

	}
}
