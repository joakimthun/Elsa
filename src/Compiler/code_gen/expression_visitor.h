#pragma once

namespace elsa {
	namespace compiler {

		class FuncDeclarationExpression;

		class ExpressionVisitor
		{
		public:
			ExpressionVisitor();

			void visit(FuncDeclarationExpression* expression);
		};

	}
}
