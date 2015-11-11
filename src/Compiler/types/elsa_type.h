#pragma once

#include <string>

#include "object_types\otype.h"
#include "constants\struct_info.h"

namespace elsa {
	namespace compiler {

		class StructDeclarationExpression;

		class ElsaType
		{
		public:
			ElsaType(const ElsaType* type);
			ElsaType(OType type);
			ElsaType(const StructDeclarationExpression* struct_declaration_expression);

			OType get_type() const;
			const StructDeclarationExpression* get_struct_declaration_expression() const;
		private:
			OType type_;
			const StructDeclarationExpression* struct_declaration_expression_;
		};

	}
}
