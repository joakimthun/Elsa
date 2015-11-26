#include "array_declaration_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		void ArrayDeclarationExpression::set_type(ElsaType * type)
		{
			type_ = std::unique_ptr<ElsaType>(type);
		}

		const ElsaType* ArrayDeclarationExpression::get_type() const
		{
			return type_.get();
		}

		void ArrayDeclarationExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
	}
}
