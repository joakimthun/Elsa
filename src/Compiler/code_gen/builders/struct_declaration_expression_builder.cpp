#include "struct_declaration_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void StructDeclarationExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, StructDeclarationExpression* expression)
		{
			auto struct_info = std::make_unique<StructInfo>(expression->get_name());

			for (const auto& field : expression->get_fields())
			{
				struct_info->add_field(new FieldInfo(field->get_name(), field->get_type()->get_type()));
			}

			program->add_struct(struct_info.release());
		}

	}
}
