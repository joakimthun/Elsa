#pragma once

#include <Windows.h>
#include <string>
#include <vector>

#include "../resource_handle.h"
#include "exceptions\runtime_exception.h"

namespace elsa {
	namespace vm {

		struct Renderable
		{
			HBRUSH brush;
			RECT rect;
		};

		class Window : public ResourceHandle
		{
		public:
			Window(const std::wstring& title, int width, int height);
			~Window();

			static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			ResourceHandleType get_type() override;

			void open();
			void update();
			void fill_rect(int x, int y, int width, int height);
		private:
			WNDCLASSEX wcex_;
			HINSTANCE hinstance_;
			HWND hwnd_;
		};
	}
}