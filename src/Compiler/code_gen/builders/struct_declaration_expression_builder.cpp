#include "struct_declaration_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void StructDeclarationExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, StructDeclarationExpression* expression)
		{
			auto name = expression->get_name();
			auto struct_info = std::make_unique<StructInfo>(name);

			for (const auto& field : expression->get_fields())
			{
				struct_info->add_field(std::make_unique<FieldInfo>(field->get_name(), field->get_type()->get_type()));
			}

			auto index = program->add_struct(std::move(struct_info));
		}

	}
}
