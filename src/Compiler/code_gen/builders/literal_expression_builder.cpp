#include "literal_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void LiteralExpressionBuilder::build(VMProgram* program, IntegerLiteralExpression* expression)
		{
			program->emit(OpCode::iconst);
			program->emit(expression->get_value());
		}

		void LiteralExpressionBuilder::build(VMProgram* program, FloatLiteralExpression* expression)
		{
			program->emit(OpCode::fconst);
			auto index = program->add_float(std::make_unique<FloatInfo>(expression->get_value()));
			program->emit(static_cast<int>(index));
		}

		void LiteralExpressionBuilder::build(VMProgram* program, CharLiteralExpression* expression)
		{
			program->emit(OpCode::cconst);
			auto index = program->add_char(std::make_unique<CharInfo>(expression->get_value()));
			program->emit(static_cast<int>(index));
		}

		void LiteralExpressionBuilder::build(VMProgram* program, BoolLiteralExpression* expression)
		{
			program->emit(OpCode::iconst);
			auto value = expression->get_value() == true ? 1 : 0;
			program->emit(static_cast<int>(value));
		}

		void LiteralExpressionBuilder::build(VMProgram* program, StringLiteralExpression* expression)
		{
			auto si = program->get_struct(L"String");

			if (si == nullptr)
				throw CodeGenException("No string struct has been defined");

			program->emit(OpCode::new_struct);
			program->emit(static_cast<int>(si->get_index()));
		}

	}
}

