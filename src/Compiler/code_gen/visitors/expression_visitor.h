#pragma once

namespace elsa {
	namespace compiler {

		class FuncDeclarationExpression;
		class VariableDeclarationExpression;
		class BinaryOperatorExpression;
		class IntegerLiteralExpression;
		class IdentifierExpression;
		class FloatLiteralExpression;
		class CharLiteralExpression;
		class StructDeclarationExpression;
		class CreateStructExpression;
		class StructAccessExpression;
		class AssignmentExpression;
		class FuncCallExpression;
		class BoolLiteralExpression;
		class ConditionalExpression;
		class LoopExpression;
		class PostfixOperatorExpression;
		class ReturnExpression;
		class ArrayDeclarationExpression;
		class ArrayAccessExpression;
		class ArrayInitializerListExpression;
		class StringLiteralExpression;

		class ExpressionVisitor
		{
		public:
			virtual ~ExpressionVisitor() {};
			virtual void visit(FuncDeclarationExpression* expression) = 0;
			virtual void visit(VariableDeclarationExpression* expression) = 0;
			virtual void visit(BinaryOperatorExpression* expression) = 0;
			virtual void visit(IntegerLiteralExpression* expression) = 0;
			virtual void visit(IdentifierExpression* expression) = 0;
			virtual void visit(FloatLiteralExpression* expression) = 0;
			virtual void visit(CharLiteralExpression* expression) = 0;
			virtual void visit(StructDeclarationExpression* expression) = 0;
			virtual void visit(CreateStructExpression* expression) = 0;
			virtual void visit(StructAccessExpression* expression) = 0;
			virtual void visit(AssignmentExpression* expression) = 0;
			virtual void visit(FuncCallExpression* expression) = 0;
			virtual void visit(BoolLiteralExpression* expression) = 0;
			virtual void visit(ConditionalExpression* expression) = 0;
			virtual void visit(LoopExpression* expression) = 0;
			virtual void visit(PostfixOperatorExpression* expression) = 0;
			virtual void visit(ReturnExpression* expression) = 0;
			virtual void visit(ArrayDeclarationExpression* expression) = 0;
			virtual void visit(ArrayAccessExpression* expression) = 0;
			virtual void visit(ArrayInitializerListExpression* expression) = 0;
			virtual void visit(StringLiteralExpression* expression) = 0;
		};

	}
}
