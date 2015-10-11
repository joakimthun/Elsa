#pragma once

#include <vector>
#include <memory>

#include "ast\expression.h"

namespace elsa {
	namespace compiler {

		class Program
		{
		public:
			Program();

			void add_expression(Expression* node);
		private:
			std::vector<std::unique_ptr<Expression>> statements_;
		};

	}
}
