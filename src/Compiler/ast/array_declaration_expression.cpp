#include "array_declaration_expression.h"

namespace elsa {
	namespace compiler {

		ArrayDeclarationExpression::ArrayDeclarationExpression(ElsaType* type)
			:
			type_(std::unique_ptr<ElsaType>(type))
		{}

		const ElsaType* ArrayDeclarationExpression::get_type() const
		{
			return type_.get();
		}

		void ArrayDeclarationExpression::accept(ExpressionVisitor* visitor)
		{
			throw "ArrayDeclarationExpression -> accept";
		}
	}
}
