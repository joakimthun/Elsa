#pragma once

#include <iostream>
#include <memory>

#include "expression_visitor.h"
#include "vm_program.h"
#include "../builders/function_builder.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor : public ExpressionVisitor
		{
		public:
			VMExpressionVisitor();
			void visit(FuncDeclarationExpression* expression) override;

		private:
			std::unique_ptr<VMProgram> vm_program_;
		};

	}
}
