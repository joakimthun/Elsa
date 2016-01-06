#pragma once

#include <string>

#include "constants\struct_info.h"
#include "object_types\vm_type.h"
#include "..\exceptions\parsing_exception.h"

namespace elsa {
	namespace compiler {

		class StructDeclarationExpression;
		class FuncDeclarationExpression;

		enum class ObjectType : int
		{
			NullPtr,
			Void,
			Int,
			Float,
			Char,
			Bool,
			GCOPtr,
			Function,
			Generic,
		};

		class ElsaType
		{
		public:
			ElsaType(const ElsaType* type);
			ElsaType(const ElsaType* type, bool is_array);
			ElsaType(ObjectType type);
			ElsaType(const StructDeclarationExpression* struct_declaration_expression);
			ElsaType(const FuncDeclarationExpression* func_declaration_expression);

			ObjectType get_type() const;
			VMType get_vm_type() const;
			std::wstring get_name() const;
			const StructDeclarationExpression* get_struct_declaration_expression() const;
			const FuncDeclarationExpression* get_func_declaration_expression() const;

			void set_is_array(bool is_array);
			bool get_is_array() const;
		private:
			void assert_is_valid();

			ObjectType type_;
			const StructDeclarationExpression* struct_declaration_expression_;
			const FuncDeclarationExpression* func_declaration_expression_;
			bool is_array_ = false;
		};

	}
}
