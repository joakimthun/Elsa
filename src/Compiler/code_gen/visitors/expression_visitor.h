#pragma once

namespace elsa {
	namespace compiler {

		class FuncDeclarationExpression;

		class ExpressionVisitor
		{
		public:
			virtual ~ExpressionVisitor() {};
			virtual void visit(FuncDeclarationExpression* expression) = 0;
		};

	}
}
