#pragma once

#include <memory>
#include <utility>

#include "expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class EnumValueExpression : public Expression
		{
		public:
			EnumValueExpression(int value);
			int get_value() const;
			const ElsaType* get_type() const;
			void set_type(ElsaType* type);

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::unique_ptr<ElsaType> type_;
			int value_;
		};
	}
}
