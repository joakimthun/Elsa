#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <cstddef>

#include "exceptions\codegen_exception.h"
#include "../expression_visitor.h"
#include "vm_program.h"
#include "../types/type_checker.h"
#include "../types/builtin/builtin.h"
#include "../interop/native_function_table.h"
#include "builders/function_declaration_expression_builder.h"
#include "builders/variable_builder.h"
#include "builders/binary_operator_expression_builder.h"
#include "builders/literal_expression_builder.h"
#include "builders/native_call_expression_builder.h"
#include "builders/identifier_expression_builder.h"
#include "builders/struct_declaration_expression_builder.h"
#include "builders/create_struct_expression_builder.h"
#include "builders/struct_access_expression_builder.h"
#include "builders/assignment_expression_builder.h"
#include "builders/func_call_expression_builder.h"
#include "builders/conditional_expression_builder.h"
#include "builders/postfix_operator_expression_builder.h"
#include "builders/loop_expression_builder.h"
#include "builders/return_expression_builder.h"
#include "builders/array_declaration_expression_builder.h"
#include "builders/array_access_expression_builder.h"
#include "builders/array_initializer_list_expression_builder.h"
#include "builders/type_cast_expression_builder.h"
#include "builders/struct_initializer_list_expression_builder.h"
#include "builders/grouped_expression_builder.h"

namespace elsa {
	namespace compiler {

		class ScopedExpression;

		class VMExpressionVisitor : public ExpressionVisitor
		{
		public:
			VMExpressionVisitor(TypeChecker* type_checker);
			void visit(FuncDeclarationExpression* expression) override;
			void visit(VariableDeclarationExpression* expression) override;
			void visit(BinaryOperatorExpression* expression) override;
			void visit(IntegerLiteralExpression* expression) override;
			void visit(IdentifierExpression* expression) override;
			void visit(FloatLiteralExpression* expression) override;
			void visit(CharLiteralExpression* expression) override;
			void visit(StructDeclarationExpression* expression) override;
			void visit(CreateStructExpression* expression) override;
			void visit(StructAccessExpression* expression) override;
			void visit(AssignmentExpression* expression) override;
			void visit(FuncCallExpression* expression) override;
			void visit(BoolLiteralExpression* expression) override;
			void visit(ConditionalExpression* expression) override;
			void visit(LoopExpression* expression) override;
			void visit(PostfixOperatorExpression* expression) override;
			void visit(ReturnExpression* expression) override;
			void visit(ArrayDeclarationExpression* expression) override;
			void visit(ArrayAccessExpression* expression) override;
			void visit(ArrayInitializerListExpression* expression) override;
			void visit(StringLiteralExpression* expression) override;
			void visit(TypeCastExpression* expression) override;
			void visit(StructInitializerListExpression* expression) override;
			void visit(GroupedExpression* expression) override;

			ScopedExpression* current_scope();
			void push_new_scope(ScopedExpression* scope);
			void pop_current_scope();

			void set_current_type(const ElsaType* type);
			const ElsaType* current_type();

			std::unique_ptr<VMProgram> release_program();
			NativeFunctionTable& native_function_table();
			TypeChecker* type_checker();

		private:
			std::unique_ptr<VMProgram> vm_program_;
			NativeFunctionTable native_function_table_;
			ScopedExpression* current_scope_;
			const ElsaType* current_type_;
			TypeChecker* type_checker_;
		};

	}
}
