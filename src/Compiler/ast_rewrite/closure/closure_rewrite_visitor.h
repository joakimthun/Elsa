#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <cstddef>

#include "../../ast/expression.h"
#include "../../exceptions/parsing_exception.h"
#include "../../parsing/elsa_parser.h"
#include "../../expression_visitor.h"
#include "../ast_rewriter.h"

namespace elsa {
	namespace compiler {

		class ScopedExpression;

		class ClosureRewriteVisitor : public ExpressionVisitor, public ASTRewriter
		{
		public:
			ClosureRewriteVisitor(Program* program, ElsaParser* parser);

			void rewrite() override;
			std::vector<std::unique_ptr<Expression>>& get_new_statements() override;

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
			void visit(ByteLiteralExpression* expression) override;
			void visit(EnumDeclarationExpression* expression) override;

			ElsaParser* parser();
			void add_statement(std::unique_ptr<Expression> node);

		private:
			void create_capture_struct(FuncDeclarationExpression* fde);
			std::size_t add_capured_identifiers_as_fields();
			void add_capured_structs_as_fields(std::size_t field_index);
			void set_captured_identifier_expressions(FuncDeclarationExpression* expression);
			void set_captured_struct_access_expressions(FuncDeclarationExpression* expression);
			void set_captured_identifiers();
			FuncDeclarationExpression* rewrite_as_member_function(VariableDeclarationExpression* vde);
			void point_variable_expression_to_member_func(VariableDeclarationExpression* vde, FuncDeclarationExpression* member_fde);
			void rewrite_captured_identifier_expression(IdentifierExpression* identifier_expression);
			void rewrite_captured_struct_access_expression(StructAccessExpression* struct_access_expression);
			void rewrite_as_assignment_expression(VariableDeclarationExpression* vde);
			bool rewrite_identifier_child();
			bool rewrite_variable_child();
			bool rewrite_struct_access_child();
			void reset_state();
			bool captured_in_closure(const std::wstring& name);
			std::wstring get_base_identifier_name();

			Program* program_;
			ElsaParser* parser_;
			std::vector<ExpressionPair<IdentifierExpression>> captured_identifier_expressions_;
			std::vector<ExpressionPair<StructAccessExpression>> captured_struct_access_expressions_;
			std::vector<std::wstring> captured_identifiers_;
			std::vector<std::unique_ptr<Expression>> statements_;
			StructDeclarationExpression* capture_struct_;
			std::wstring capture_variable_name_;
			std::unique_ptr<StructAccessExpression> next_identifier_rewrite_;
			std::unique_ptr<AssignmentExpression> next_variable_rewrite_;
			std::unique_ptr<StructAccessExpression> next_struct_access_rewrite_;
			bool inside_nested_func_;
		};

	}
}
