#pragma once

#include "expression_visitor.h"

#include <iostream>

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor : public ExpressionVisitor
		{
		public:
			VMExpressionVisitor();
			void visit(FuncDeclarationExpression* expression) override;
		};

	}
}
