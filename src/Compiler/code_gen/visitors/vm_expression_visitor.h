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
#include "../../symbol_tables/struct_table.h"
#include "../../symbol_tables/function_table.h"
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

		class VMExpressionVisitor : public ExpressionVisitor
		{
		public:
			VMExpressionVisitor(FunctionTable* function_table, StructTable* struct_table);
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

			std::unique_ptr<VMProgram> release_program();

			NativeFunctionTable& native_function_table();
			StructTable* struct_table();
			FunctionTable* function_table();
			void increment_scope_nesting();
			void reset_scope_nesting();
			const LocalSymbol* get_local(const std::wstring& name) const;
			void set_current_function(const std::wstring& name);
			void reset_current_function();

		private:
			std::unique_ptr<VMProgram> vm_program_;
			StructTable* struct_table_;
			FunctionTable* function_table_;
			NativeFunctionTable native_function_table_;
			FunctionSymbol* current_function_;
			std::size_t scope_nesting_;
		};

	}
}
