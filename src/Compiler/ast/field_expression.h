#pragma once

#include <string>
#include <memory>
#include <cstddef>

#include "expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class FieldExpression : public Expression
		{
		public:
			FieldExpression();
			FieldExpression(const std::wstring& name, const ElsaType* type, std::size_t index);

			void set_name(const std::wstring& name);
			void set_type(ElsaType* type);
			void set_index(std::size_t index);
			void set_is_array(bool is_array);

			const std::wstring& get_name() const;
			const ElsaType* get_type() const;
			std::size_t get_index() const;
			bool get_is_array() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring name_;
			std::unique_ptr<ElsaType> type_;
			std::size_t index_;
			bool is_array_;
		};
	}
}
