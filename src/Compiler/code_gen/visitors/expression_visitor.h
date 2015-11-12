#pragma once

namespace elsa {
	namespace compiler {

		class FuncDeclarationExpression;
		class VariableDeclarationExpression;
		class BinaryOperatorExpression;
		class IntegerLiteralExpression;
		class ElsaInvokeExpression;
		class IdentifierExpression;
		class FloatLiteralExpression;
		class CharLiteralExpression;
		class StructDeclarationExpression;
		class CreateStructExpression;
		class StructAccessExpression;
		class AssignmentExpression;

		class ExpressionVisitor
		{
		public:
			virtual ~ExpressionVisitor() {};
			virtual void visit(FuncDeclarationExpression* expression) = 0;
			virtual void visit(VariableDeclarationExpression* expression) = 0;
			virtual void visit(BinaryOperatorExpression* expression) = 0;
			virtual void visit(IntegerLiteralExpression* expression) = 0;
			virtual void visit(ElsaInvokeExpression* expression) = 0;
			virtual void visit(IdentifierExpression* expression) = 0;
			virtual void visit(FloatLiteralExpression* expression) = 0;
			virtual void visit(CharLiteralExpression* expression) = 0;
			virtual void visit(StructDeclarationExpression* expression) = 0;
			virtual void visit(CreateStructExpression* expression) = 0;
			virtual void visit(StructAccessExpression* expression) = 0;
			virtual void visit(AssignmentExpression* expression) = 0;
		};

	}
}
