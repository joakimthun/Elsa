#pragma once

#include <memory>

#include "exceptions\codegen_exception.h"
#include "../../ast/integer_literal_expression.h"
#include "../../ast/float_literal_expression.h"
#include "../../ast/char_literal_expression.h"
#include "../../ast/bool_literal_expression.h"
#include "../../ast/string_literal_expression.h"
#include "../../ast/byte_literal_expression.h"
#include "../../ast/enum_value_expression.h"
#include "opcodes\opcodes.h"
#include "vm_program.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class LiteralExpressionBuilder
		{
		public:
			static void build(VMProgram* program, IntegerLiteralExpression* expression);
			static void build(VMProgram* program, FloatLiteralExpression* expression);
			static void build(VMProgram* program, CharLiteralExpression* expression);
			static void build(VMProgram* program, BoolLiteralExpression* expression);
			static void build(VMProgram* program, StringLiteralExpression* expression);
			static void build(VMProgram* program, ByteLiteralExpression* expression);
			static void build(VMProgram* program, EnumValueExpression* expression);
		};

	}
}