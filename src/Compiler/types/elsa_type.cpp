#include "elsa_type.h"

#include "../ast/struct_declaration_expression.h"

namespace elsa {
	namespace compiler {

		ElsaType::ElsaType(OType type)
			:
			type_(type)
		{}

		ElsaType::ElsaType(const StructDeclarationExpression* struct_declaration_expression)
			:
			type_(OType::UserDefined),
			struct_declaration_expression_(struct_declaration_expression)
		{}

		OType ElsaType::get_type() const
		{
			return type_;
		}

		const StructDeclarationExpression* ElsaType::get_struct_declaration_expression() const
		{
			return struct_declaration_expression_;
		}
	}
}
