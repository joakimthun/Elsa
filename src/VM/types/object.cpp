#include "object.h"

namespace elsa {
	namespace vm {

		Object::Object()
		{
			type_ = Undefined;
		}

		Object::Object(int v)
		{
			value_.i = v;
			type_ = Int;
		};

		Object::Object(float v)
		{
			value_.f = v;
			type_ = Float;
		};

		Object::Object(wchar_t v)
		{
			value_.c = v;
			type_ = Char;
		}

		Object::Object(GCObject* o)
		{
			value_.gco = o;
			type_ = GCOPtr;
		}

		int Object::i() const
		{
			if (type_ == Int)
				return value_.i;

			throw RuntimeException("Can not get an integer value from a non integer type.");
		}

		float Object::f() const
		{
			if (type_ == Float)
				return value_.f;

			throw RuntimeException("Can not get a float value from a non float type.");
		}

		wchar_t Object::c() const
		{
			if (type_ == Char)
				return value_.c;

			throw RuntimeException("Can not get a char value from a non char type.");
		}

		bool Object::b() const
		{
			if (type_ == Bool)
				return value_.b;

			throw RuntimeException("Can not get a boolean value from a non bool type.");
		}

		GCObject* Object::gco() const
		{
			if (type_ == GCOPtr)
				return value_.gco;

			throw RuntimeException("Can not get a GCObject pointer from a non GCObject pointer type.");
		}

		OType Object::get_type() const
		{
			return type_;
		}

		void Object::set_type(OType type)
		{
			type_ = type;
		}
	}
}
