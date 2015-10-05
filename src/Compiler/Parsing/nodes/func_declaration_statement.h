#pragma once

#include <string>
#include <memory>
#include <vector>

#include "statement.h"
#include "expression.h"

namespace elsa {
	namespace compiler {

		struct FuncDeclarationStatement : public Statement
		{
			std::wstring name;
			std::vector<std::unique_ptr<Expression>> body;
		};

	}
}
