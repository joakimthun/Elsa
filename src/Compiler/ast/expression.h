#pragma once

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class Expression
		{
		public:
			virtual ~Expression() {};
			virtual void accept(ExpressionVisitor* visitor) {}
		};

	}
}
