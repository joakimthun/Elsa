#include "struct_declaration_expression.h"

#include "../code_gen/visitors/expression_visitor.h"
#include "../parsing/elsa_parser.h"

namespace elsa {
	namespace compiler {

		StructDeclarationExpression::StructDeclarationExpression()
			:
			is_generic_(false),
			parent_(nullptr)
		{
		}

		StructDeclarationExpression::StructDeclarationExpression(bool is_generic)
			:
			is_generic_(is_generic),
			parent_(nullptr)
		{
		}

		const StructDeclarationExpression* StructDeclarationExpression::create_generic(std::unique_ptr<ElsaType> type, ElsaParser* parser) const
		{
			if (!is_generic_)
				throw ElsaException("Not a generic type");

			auto name = name_ + L"___" + type->get_name();

			if (parser->struct_table().has_entry(name))
				return parser->struct_table().get(name)->get_expression();

			auto new_type = std::make_unique<StructDeclarationExpression>();
			new_type->parent_ = this;
			new_type->name_ = name;
			new_type->is_generic_ = is_generic_;

			for (const auto& field : fields_)
			{
				const auto field_type = field->get_type()->get_type() == ObjectType::Generic ? type.get() : field->get_type();
				new_type->add_field_expression(std::make_unique<FieldExpression>(field->get_name(), type.get(), field->get_index()));
			}

			for (const auto& function : functions_)
			{
				new_type->add_member_function(function->create_generic(type.get()));
			}

			new_type->generic_type_ = std::move(type);

			parser->struct_table().add_struct(new_type->get_name(), new_type.get());

			return new_type.release();
		}

		void StructDeclarationExpression::set_name(const std::wstring& name)
		{
			name_ = name;
		}

		void StructDeclarationExpression::add_field_expression(std::unique_ptr<FieldExpression> expression)
		{
			fields_.push_back(std::move(expression));
			fields_.back()->set_index(fields_.size() - 1);
		}

		void StructDeclarationExpression::add_member_function(std::unique_ptr<FuncDeclarationExpression> expression)
		{
			functions_.push_back(std::move(expression));
		}

		const FuncDeclarationExpression* StructDeclarationExpression::get_member_function(const std::wstring& name) const
		{
			for (const auto& f : functions_)
			{
				if (f->get_name() == name)
					return f.get();
			}

			throw ParsingException("Undefined member function");
		}

		const ElsaType* StructDeclarationExpression::get_generic_type() const
		{
			return generic_type_.get();
		}

		bool StructDeclarationExpression::is_generic_type() const
		{
			return is_generic_;
		}

		const std::wstring& StructDeclarationExpression::get_name(bool inherited) const
		{
			if (inherited && parent_ != nullptr)
				return parent_->get_name(true);

			return name_;
		}

		const std::vector<std::unique_ptr<FieldExpression>>& StructDeclarationExpression::get_fields() const
		{
			return fields_;
		}

		const std::vector<std::unique_ptr<FuncDeclarationExpression>>& StructDeclarationExpression::get_functions() const
		{
			return functions_;
		}

		void StructDeclarationExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
	}
}

