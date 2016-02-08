#include "object.h"

namespace elsa {
	namespace vm {

		Object::Object()
		{
			type_ = VMType::NullPtr;
		}

		Object::Object(int v)
		{
			value_.i = v;
			type_ = VMType::Int;
		};

		Object::Object(float v)
		{
			value_.f = v;
			type_ = VMType::Float;
		};

		Object::Object(wchar_t v)
		{
			value_.c = v;
			type_ = VMType::Char;
		}

		Object::Object(GCObject* o)
		{
			value_.gco = o;
			type_ = VMType::GCOPtr;
		}

		Object::Object(bool v)
		{
			auto value = v == true ? 1 : 0;
			value_.i = value;
			type_ = VMType::Int;
		}

		int Object::i() const
		{
			if (type_ == VMType::Int)
				return value_.i;

			throw RuntimeException("Can not get an integer value from a non integer type.");
		}

		float Object::f() const
		{
			if (type_ == VMType::Float)
				return value_.f;

			throw RuntimeException("Can not get a float value from a non float type.");
		}

		wchar_t Object::c() const
		{
			if (type_ == VMType::Char)
				return value_.c;

			throw RuntimeException("Can not get a char value from a non char type.");
		}

		GCObject* Object::gco() const
		{
			if (type_ == VMType::GCOPtr)
				return value_.gco;

			throw RuntimeException("Can not get a GCObject pointer from a non GCObject pointer type.");
		}

		GCObject* Object::function() const
		{
			if (type_ == VMType::Function)
				return value_.gco;

			throw RuntimeException("Can not get an address from a non function type.");
		}

		const Value & Object::get_value() const
		{
			return value_;
		}

		elsa::VMType Object::get_type() const
		{
			return type_;
		}

		void Object::set_type(elsa::VMType type)
		{
			type_ = type;
		}
	}
}
