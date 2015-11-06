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
#include "../../symbol_tables/struct_table.h"
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

			void push_new_scope();
			void pop_current_scope();
			void push_current_scope(const std::wstring& name, const ElsaType& type);
			bool current_scope_has_entry(const std::wstring& name);
			const LocalSymbol* get_local(const std::wstring& name) const;

			void add_struct(const std::wstring& name, std::size_t index);
			bool has_struct_entry(const std::wstring& name);
			const StructSymbol* get_struct(const std::wstring& name);

			std::unique_ptr<VMProgram> release_program();
			void set_current_function(FunctionInfo* fi);
			FunctionInfo* get_current_function();
			void reset_current_function();

			NativeFunctionTable& get_native_function_table();

		private:
			std::unique_ptr<VMProgram> vm_program_;
			std::vector<std::unique_ptr<LocalTable>> local_table_;
			StructTable struct_table_;
			FunctionInfo* current_function_;
			NativeFunctionTable native_function_table_;
		};

	}
}
