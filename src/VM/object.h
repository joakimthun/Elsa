#pragma once

namespace elsa {
	namespace vm {

		enum TValue {
			Int,
			Float,
			Char
		};

		typedef union {
			int i;
			float f;
			char c;
		} Value;

		class Object
		{
		public:
			Object(int v);
			Object(float v);
			Object(char v);

			int i();
			float f();
			char c();

		private:
			TValue type_;
			Value value_;
		};

	}
}