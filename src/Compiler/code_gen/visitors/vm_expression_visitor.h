#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <cstddef>

#include "exceptions\codegen_exception.h"
#include "expression_visitor.h"
#include "vm_program.h"
#include "../../interop/native_function_table.h"
#include "../builders/function_declaration_expression_builder.h"
#include "../builders/variable_builder.h"
#include "../builders/binary_operator_expression_builder.h"
#include "../builders/literal_expression_builder.h"
#include "../builders/elsa_invoke_expression_builder.h"
#include "../builders/identifier_expression_builder.h"
#include "../builders/struct_declaration_expression_builder.h"
#include "../builders/create_struct_expression_builder.h"

namespace elsa {
	namespace compiler {

		class ScopedExpression;

		class VMExpressionVisitor : public ExpressionVisitor
		{
		public:
			VMExpressionVisitor();
			void visit(FuncDeclarationExpression* expression) override;
			void visit(VariableDeclarationExpression* expression) override;
			void visit(BinaryOperatorExpression* expression) override;
			void visit(IntegerLiteralExpression* expression) override;
			void visit(ElsaInvokeExpression* expression) override;
			void visit(IdentifierExpression* expression) override;
			void visit(FloatLiteralExpression* expression) override;
			void visit(CharLiteralExpression* expression) override;
			void visit(StructDeclarationExpression* expression) override;
			void visit(CreateStructExpression* expression) override;
			void visit(StructAccessExpression* expression) override;

			ScopedExpression* current_scope();
			void set_current_scope(ScopedExpression* scope);
			void reset_current_scope();

			std::unique_ptr<VMProgram> release_program();
			NativeFunctionTable& native_function_table();

		private:
			std::unique_ptr<VMProgram> vm_program_;
			NativeFunctionTable native_function_table_;
			ScopedExpression* current_scope_;
		};

	}
}
