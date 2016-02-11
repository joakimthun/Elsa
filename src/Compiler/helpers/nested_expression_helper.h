#pragma once

#include <vector>

#include "../ast/variable_declaration_expression.h"
#include "../ast/func_declaration_expression.h"
#include "../ast/conditional_expression.h"
#include "../ast/loop_expression.h"
#include "../ast/return_expression.h"
#include "../ast/func_call_expression.h"
#include "../ast/binary_operator_expression.h"

namespace elsa {
	namespace compiler {

		template<typename TExpression>
		struct ExpressionPair
		{
			TExpression* expression;
			Expression* parent;
		};

		class NestedExpressionHelper
		{
		public:
			template<typename TExpression>
			static std::vector<ExpressionPair<TExpression>> get_nested_expressions(Expression* exp)
			{
				auto expressions = std::vector<ExpressionPair<TExpression>>();
				get_nested_expressions(exp, expressions, exp);
				return expressions;
			}

			template<typename TExpression>
			static void get_nested_expressions(Expression* exp, std::vector<ExpressionPair<TExpression>>& expressions, Expression* parent)
			{
				auto target_ext = dynamic_cast<TExpression*>(exp);
				if (target_ext != nullptr)
				{
					auto pair = ExpressionPair<TExpression>();
					pair.expression = target_ext;
					pair.parent = parent;

					expressions.push_back(pair);
				}

				if (auto vde = dynamic_cast<VariableDeclarationExpression*>(exp))
				{
					get_nested_expressions(vde->get_expression(), expressions, vde);
				}
				else if (auto conde_exp = dynamic_cast<ConditionalExpression*>(exp))
				{
					for (const auto& ie : conde_exp->get_if_body())
					{
						get_nested_expressions(ie.get(), expressions, conde_exp);
					}

					for (const auto& ee : conde_exp->get_else_body())
					{
						get_nested_expressions(ee.get(), expressions, conde_exp);
					}
				}
				else if (auto loop_exp = dynamic_cast<LoopExpression*>(exp))
				{
					for (const auto& be : loop_exp->get_body())
					{
						get_nested_expressions(be.get(), expressions, loop_exp);
					}
				}
				else if (auto ret_exp = dynamic_cast<ReturnExpression*>(exp))
				{
					get_nested_expressions(ret_exp->get_expression(), expressions, ret_exp);
				}
				else if (auto fde = dynamic_cast<FuncDeclarationExpression*>(exp))
				{
					for (const auto& body_exp : fde->get_body())
					{
						get_nested_expressions(body_exp.get(), expressions, fde);
					}

					for (const auto& arg_exp : fde->get_args())
					{
						get_nested_expressions(arg_exp.get(), expressions, fde);
					}
				}
				else if (auto fc_exp = dynamic_cast<FuncCallExpression*>(exp))
				{
					for (const auto& arg : fc_exp->get_args())
					{
						get_nested_expressions(arg.get(), expressions, fc_exp);
					}
				}
				else if (auto bo_exp = dynamic_cast<BinaryOperatorExpression*>(exp))
				{
					get_nested_expressions(bo_exp->get_left(), expressions, bo_exp);
					get_nested_expressions(bo_exp->get_right(), expressions, bo_exp);
				}
			}
		};

	}
}
