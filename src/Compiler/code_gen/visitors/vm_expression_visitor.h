#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "exceptions\codegen_exception.h"
#include "expression_visitor.h"
#include "vm_program.h"
#include "../../symbol_tables/local_table.h"
#include "../builders/function_builder.h"
#include "../builders/variable_builder.h"
#include "../builders/binary_operator_expression_builder.h"

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

			void push_new_scope();
			void pop_current_scope();
			void push_current_scope(const std::wstring& name, const ElsaType& type);
			bool current_scope_has_entry(std::wstring name);
			const LocalSymbol* get_from_current_scope(std::wstring name) const;

		private:
			std::unique_ptr<VMProgram> vm_program_;
			std::vector<std::unique_ptr<LocalTable>> local_table_;
		};

	}
}
