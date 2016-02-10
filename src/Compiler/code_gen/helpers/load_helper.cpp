#include "load_helper.h"

#include "../vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		std::size_t LoadHelper::load_field(VMProgram* program, VMExpressionVisitor* visitor, StructAccessExpression* sae, bool load_target_field)
		{
			IdentifierExpressionBuilder::build(program, visitor, sae->get_base());

			auto current_type = sae->get_base()->get_type()->get_struct_declaration_expression();
			for (auto it = sae->get_expressions().begin(); it != sae->get_expressions().end(); ++it)
			{
				for (const auto& field : current_type->get_fields())
				{
					if (field->get_name() == it->get()->get_name())
					{
						// Last element, return the field index
						if (std::next(it) == sae->get_expressions().end())
						{
							if (load_target_field)
							{
								load_field_internal(program, field.get());
							}

							return field->get_index();
						}
						else
						{
							if (field->get_type()->get_type() == ObjectType::GCOPtr)
								current_type = field->get_type()->get_struct_declaration_expression();

							load_field_internal(program, field.get());
						}

						break;
					}
				}
			}

			throw CodeGenException("Invalid StructAccessExpression -> StoreHelper::store_field");
		}

		std::size_t LoadHelper::load_local(VMProgram* program, VMExpressionVisitor* visitor, IdentifierExpression* ie)
		{
			IdentifierExpressionBuilder::build(program, visitor, ie);
			auto local = visitor->current_scope()->get_local(ie->get_name());
			return local->get_index();
		}

		void LoadHelper::load_field_internal(VMProgram* program, const FieldExpression* field)
		{
			program->emit(OpCode::l_field);
			program->emit(static_cast<int>(field->get_index()));
		}

	}
}

