#include "windows.h"


namespace elsa {
	namespace vm {

		void peek_message()
		{
			MSG msg;
			if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
}
