#pragma once

#include <string>

namespace elsa {
	namespace compiler {

		class ElsaType;

		enum class ExpressionType 
		{
			FieldAccess,
			FuncCall,
			ArrayAccess,
			Identifier
		};

		class TypedExpression
		{
		public:
			virtual ~TypedExpression() {};
			virtual const std::wstring& get_name() const = 0;
			virtual const ElsaType* get_type() const = 0;
			virtual ExpressionType get_expression_type() const = 0;
		};

	}
}

