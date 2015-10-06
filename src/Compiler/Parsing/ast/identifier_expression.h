#pragma once

#include <string>

#include "expression.h"

namespace elsa {
	namespace compiler {

		class IdentifierExpression : public Expression
		{
		public:
			IdentifierExpression(const std::wstring& name);

		private:
			std::wstring name_;
		};

	}
}
