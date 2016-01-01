#include "elsa_type.h"

#include "../ast/struct_declaration_expression.h"

namespace elsa {
	namespace compiler {

		ElsaType::ElsaType(const ElsaType* type)
			:
			type_(type->get_type()),
			struct_declaration_expression_(type->get_struct_declaration_expression())
		{
		}

		ElsaType::ElsaType(const ElsaType* type, bool is_array)
			:
			type_(type->get_type()),
			struct_declaration_expression_(nullptr),
			is_array_(is_array)
		{
		}

		ElsaType::ElsaType(ObjectType type)
			:
			type_(type),
			struct_declaration_expression_(nullptr)
		{}

		ElsaType::ElsaType(const StructDeclarationExpression* struct_declaration_expression)
			:
			type_(ObjectType::GCOPtr),
			struct_declaration_expression_(struct_declaration_expression)
		{}

		ObjectType ElsaType::get_type() const
		{
			return type_;
		}

		VMType ElsaType::get_vm_type() const
		{
			switch (type_)
			{
			case ObjectType::Bool:
			case ObjectType::Int: {
				return VMType::Int;
			}
			case ObjectType::Float: {
				return VMType::Float;
			}
			case ObjectType::Char: {
				return VMType::Char;
			}
			case ObjectType::GCOPtr: {
				return VMType::GCOPtr;
			}
			default:
				throw ParsingException("Unsupported field type.");
			}
		}

		const StructDeclarationExpression* ElsaType::get_struct_declaration_expression() const
		{
			return struct_declaration_expression_;
		}

		void ElsaType::set_is_array(bool is_array)
		{
			is_array_ = is_array;
		}

		bool ElsaType::get_is_array() const
		{
			return is_array_;
		}
	}
}
