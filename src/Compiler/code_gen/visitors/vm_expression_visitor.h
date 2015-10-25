#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "expression_visitor.h"
#include "vm_program.h"
#include "../builders/function_builder.h"
#include "../../symbol_tables/local_table.h"

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
			void push_current(LocalSymbol* symbol);
			bool has_entry(std::wstring name);

		private:
			std::unique_ptr<VMProgram> vm_program_;
			std::vector<std::unique_ptr<LocalTable>> local_table_;
		};

	}
}
