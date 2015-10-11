#pragma once

#include <string>

#include "expression.h"

namespace elsa {
	namespace compiler {

		class IdentifierExpression : public Expression
		{
		public:
			IdentifierExpression(const std::wstring& name);

			const std::wstring& get_name() const;

		private:
			std::wstring name_;
		};

	}
}
