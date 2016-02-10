#include "struct_declaration_expression_builder.h"

#include "../vm_expression_visitor.h"
#include "function_declaration_expression_builder.h"

namespace elsa {
	namespace compiler {

		void StructDeclarationExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, StructDeclarationExpression* expression)
		{
			auto name = expression->get_name();
			auto struct_info = std::make_unique<StructInfo>(name);
			auto struct_info_ptr = struct_info.get();
			program->add_struct(std::move(struct_info));

			for (const auto& field : expression->get_fields())
			{
				struct_info_ptr->add_field(std::make_unique<FieldInfo>(field->get_name(), field->get_type()->get_vm_type()));
			}

			for (const auto& func : expression->get_functions())
			{
				visitor->set_current_type(expression->get_type());
				struct_info_ptr->add_function(FunctionDeclarationExpressionBuilder::build_member(program, visitor, func.get()));
				visitor->set_current_type(nullptr);
			}
		}

	}
}
