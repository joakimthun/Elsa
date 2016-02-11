#include "ast_rewrite_expression_visitor.h"

namespace elsa {
	namespace compiler {

		ASTRewriteExpressionVisitor::ASTRewriteExpressionVisitor(ElsaParser* parser)
			:
			parser_(parser)
		{
		}

		void ASTRewriteExpressionVisitor::visit(FuncDeclarationExpression* expression)
		{
			ClosureRewriter::rewrite(this, expression);
		}

		void ASTRewriteExpressionVisitor::visit(VariableDeclarationExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(BinaryOperatorExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(IntegerLiteralExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(IdentifierExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(FloatLiteralExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(CharLiteralExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(StructDeclarationExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(CreateStructExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(StructAccessExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(AssignmentExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(FuncCallExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(BoolLiteralExpression * expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(ConditionalExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(LoopExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(PostfixOperatorExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(ReturnExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(ArrayDeclarationExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(ArrayAccessExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(ArrayInitializerListExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(StringLiteralExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(TypeCastExpression* expression)
		{
		}

		void ASTRewriteExpressionVisitor::visit(StructInitializerListExpression* expression)
		{
		}

		ElsaParser* ASTRewriteExpressionVisitor::parser()
		{
			return parser_;
		}

		void ASTRewriteExpressionVisitor::add_statement(std::unique_ptr<Expression> node)
		{
			statements_.push_back(std::move(node));
		}

		std::vector<std::unique_ptr<Expression>>& ASTRewriteExpressionVisitor::get_statements()
		{
			return statements_;
		}

	}
}