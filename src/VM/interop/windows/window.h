#pragma once

#include <Windows.h>

#include "../resource_handle.h"
#include "exceptions\runtime_exception.h"

namespace elsa {
	namespace vm {

		class Window : public ResourceHandle
		{
		public:
			Window();
			~Window();

			static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			ResourceHandleType get_type() override;

			void Open();
		private:
			WNDCLASSEX wcex_;
			HINSTANCE hinstance_;
			HWND hwnd_;
		};
	}
}