#pragma once

#include <vector>
#include <memory>

#include "exceptions\parsing_exception.h"
#include "ast\expression.h"
#include "symbol_tables\function_table.h"

namespace elsa {
	namespace compiler {

		class Program
		{
		public:
			Program();

			void add_statement(Expression* node);
			void add_function(FunctionSymbol* function);

		private:
			std::vector<std::unique_ptr<Expression>> statements_;
			FunctionTable functions_;
		};

	}
}
