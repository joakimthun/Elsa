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

		Object::Object(void* ptr, OType type)
		{
			value_.ptr = ptr;
			type_ = type;
		}

		int Object::i() const
		{
			if (type_ == Int)
				return value_.i;
			if (type_ == IPtr)
				return *(int*)value_.ptr;

			throw RuntimeException("Can not get an integer value from a non integer type.");
		}

		float Object::f() const
		{
			if (type_ == Float)
				return value_.f;
			if (type_ == FPtr)
				return *(float*)value_.ptr;

			throw RuntimeException("Can not get a float value from a non float type.");
		}

		wchar_t Object::c() const
		{
			if (type_ == Char)
				return value_.c;
			if (type_ == CPtr)
				return *(wchar_t*)value_.ptr;

			throw RuntimeException("Can not get a char value from a non char type.");
		}

		bool Object::b() const
		{
			if (type_ == Bool)
				return value_.b;
			if (type_ == BPtr)
				return *(bool*)value_.ptr;

			throw RuntimeException("Can not get a boolean value from a non bool type.");
		}

		void* Object::ptr() const
		{
			return value_.ptr;
		}

		OType Object::get_type() const
		{
			return type_;
		}
	}
}
