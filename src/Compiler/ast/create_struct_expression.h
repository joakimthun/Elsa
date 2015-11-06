#pragma once

#include <string>
#include <memory>

#include "expression.h"
#include "exceptions\elsa_exception.h"

namespace elsa {
	namespace compiler {

		class CreateStructExpression : public Expression
		{
		public:
			CreateStructExpression(const std::wstring& name);

			const std::wstring& get_struct_name() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring struct_name_;
		};
	}
}
