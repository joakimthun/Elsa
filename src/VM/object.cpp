#include "object.h"

namespace elsa {
	namespace vm {
		
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

		Object::Object(char v)
		{
			value_.c = v;
			type_ = Char;
		};

		int Object::i() const
		{
			return value_.i;
		}

		float Object::f() const
		{
			return value_.f;
		}

		char Object::c() const
		{
			return value_.c;
		}

		OType Object::get_type() const
		{
			return type_;
		}
	}
}
