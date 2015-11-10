#pragma once

#include <vector>
#include <memory>
#include <utility>

#include "exceptions\parsing_exception.h"
#include "ast\expression.h"
#include "symbol_tables\function_table.h"
#include "symbol_tables\struct_table.h"

namespace elsa {
	namespace compiler {

		class Program
		{
		public:
			Program(FunctionTable* function_table, StructTable* struct_table);

			void add_statement(std::unique_ptr<Expression> node);
			void add_function(FunctionSymbol* function);
			std::vector<std::unique_ptr<Expression>>& get_statements();
			FunctionTable* function_table();
			StructTable* struct_table();

		private:
			std::vector<std::unique_ptr<Expression>> statements_;
			FunctionTable* function_table_;
			StructTable* struct_table_;
		};

	}
}
