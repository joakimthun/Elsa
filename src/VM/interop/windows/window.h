#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdint.h>

#include "../resource_handle.h"
#include "exceptions\runtime_exception.h"

namespace elsa {
	namespace vm {

		class Window : public ResourceHandle
		{
		public:
			Window(const std::wstring& title, int width, int height);
			~Window();

			static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			
			ResourceHandleType get_type() override;

			void open();
			void update();
			void fill_rect(int x, int y, int width, int height, int r, int g, int b);
			void fill_circle(int x, int y, int diameter, int r, int g, int b);
			bool key_down(WPARAM keycode);
			void render_text(int x, int y, const std::wstring& str);
			void blt(int x, int y, int width, int height, uint8_t* src);
		private:
			WNDCLASSEX wcex_;
			HINSTANCE hinstance_;
			HWND hwnd_;
		};
	}
}
