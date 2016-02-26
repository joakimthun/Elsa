#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <utility>

#include "expression.h"
#include "../types/elsa_type.h"
#include "../exceptions/parsing_exception.h"

namespace elsa {
	namespace compiler {

		class EnumDeclarationExpression : public Expression
		{
		public:
			void set_name(const std::wstring& name);
			void add_value(const std::wstring& name, int value);
			int get_value(const std::wstring& name) const;
			const ElsaType* get_type() const;
			void set_type(ElsaType* type);

			const std::wstring& get_name() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::unique_ptr<ElsaType> type_;
			std::wstring name_;
			std::unordered_map<std::wstring, int> members_;
		};
	}
}
