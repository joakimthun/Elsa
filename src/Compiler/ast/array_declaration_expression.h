#pragma once

#include <memory>

#include "expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class ArrayDeclarationExpression : public Expression
		{
		public:
			ArrayDeclarationExpression(ElsaType* type);
			const ElsaType* get_type() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::unique_ptr<ElsaType> type_;
		};
	}
}