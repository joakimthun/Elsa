#pragma once

#include <string>
#include <memory>

#include "expression.h"
#include "exceptions\elsa_exception.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class CreateStructExpression : public Expression
		{
		public:
			CreateStructExpression(const std::wstring& name, ElsaType* type);

			const std::wstring& get_struct_name() const;
			const ElsaType* get_type() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring struct_name_;
			std::unique_ptr<ElsaType> type_;
		};
	}
}
