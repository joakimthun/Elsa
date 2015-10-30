#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>

#include "exceptions\codegen_exception.h"
#include "expression_visitor.h"
#include "vm_program.h"
#include "../../symbol_tables/local_table.h"
#include "../../interop/native_function_table.h"
#include "../builders/function_builder.h"
#include "../builders/variable_builder.h"
#include "../builders/binary_operator_expression_builder.h"
#include "../builders/literal_expression_builder.h"
#include "../builders/elsa_invoke_expression_builder.h"
#include "../builders/identifier_expression_builder.h"

namespace elsa {
	namespace compiler {

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

			void push_new_scope();
			void pop_current_scope();
			void push_current_scope(const std::wstring& name, const ElsaType& type);
			bool current_scope_has_entry(std::wstring name);
			const LocalSymbol* get_local(std::wstring name) const;

			std::unique_ptr<VMProgram> release_program();
			void set_current_function(FunctionInfo* fi);
			FunctionInfo* get_current_function();
			void reset_current_function();

			NativeFunctionTable& get_native_function_table();

		private:
			std::unique_ptr<VMProgram> vm_program_;
			std::vector<std::unique_ptr<LocalTable>> local_table_;
			FunctionInfo* current_function_;
			NativeFunctionTable native_function_table_;
		};

	}
}
