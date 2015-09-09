#pragma once

namespace elsa {
	namespace vm {

		enum OType {
			Int,
			Float,
			Char,
			Undefined
		};

		typedef union {
			int i;
			float f;
			char c;
		} Value;

		class Object
		{
		public:
			Object();
			Object(int v);
			Object(float v);
			Object(char v);

			int i() const;
			float f() const;
			char c() const;
			OType get_type() const;

		private:
			OType type_;
			Value value_;
		};

	}
}