#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <cstddef>

#include "../exceptions/parsing_exception.h"
#include "../parsing/elsa_parser.h"
#include "../expression_visitor.h"

namespace elsa {
	namespace compiler {

		class ScopedExpression;

		class ASTRewriteExpressionVisitor : public ExpressionVisitor
		{
		public:
			ASTRewriteExpressionVisitor(ElsaParser* parser);
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

		private:
			ElsaParser* parser_;
		};

	}
}
