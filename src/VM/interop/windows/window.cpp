#include "window.h"

namespace elsa {
	namespace vm {

		// Refactor this if support for multiple windows is added
		HDC mem_hdc;
		HBITMAP bitmap;

		Window::Window(const std::wstring& title, int width, int height)
		{
			hinstance_ = GetModuleHandle(NULL);

			wcex_.cbSize = sizeof(WNDCLASSEX);
			wcex_.style = CS_HREDRAW | CS_VREDRAW;
			wcex_.lpfnWndProc = WndProc;
			wcex_.cbClsExtra = 0;
			wcex_.cbWndExtra = 0;
			wcex_.hInstance = hinstance_;
			wcex_.hIcon = LoadIcon(hinstance_, MAKEINTRESOURCE(IDI_APPLICATION));
			wcex_.hCursor = LoadCursor(NULL, IDC_ARROW);
			wcex_.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wcex_.lpszMenuName = NULL;
			wcex_.lpszClassName = L"ElsaWindow";
			wcex_.hIconSm = LoadIcon(wcex_.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

			if (!RegisterClassEx(&wcex_))
			{
				MessageBox(NULL, L"Call to RegisterClassEx failed!", L"ElsaWindow", NULL);

				throw RuntimeException("Could not create window, call to RegisterClassEx failed");
			}

			DWORD window_style = WS_OVERLAPPEDWINDOW;
			RECT client_rect = { 0, 0, width, height };
			if (!AdjustWindowRectEx(&client_rect, window_style, false, NULL))
			{
				throw RuntimeException("Could not create window, call to AdjustWindowRectEx failed");
			}

			hwnd_ = CreateWindow(
				L"ElsaWindow",
				title.c_str(),
				window_style,
				CW_USEDEFAULT, 
				CW_USEDEFAULT,
				// width
				client_rect.right - client_rect.left, 
				// height
				client_rect.bottom - client_rect.top,
				NULL,
				NULL,
				hinstance_,
				NULL
				);

#ifdef _DEBUG
			GetClientRect(hwnd_, &client_rect);
			if (client_rect.right != width || client_rect.bottom != height)
			{
				throw RuntimeException("Invalid client area size");
			}
#endif

			if (!hwnd_)
			{
				throw RuntimeException("Could not create window, call to CreateWindow failed");
			}

			HDC hdc = GetDC(hwnd_);
			mem_hdc = CreateCompatibleDC(hdc);
			bitmap = CreateCompatibleBitmap(hdc, width, height);

			SelectObject(mem_hdc, bitmap);
		}

		Window::~Window() 
		{

		}

		LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_PAINT: {
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				auto width = ps.rcPaint.right;
				auto height = ps.rcPaint.bottom;
				BitBlt(hdc, 0, 0, width, height, mem_hdc, 0, 0, SRCCOPY);
				EndPaint(hWnd, &ps);
				break;
			}
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
				break;
			}

			return 0;
		}

		ResourceHandleType Window::get_type()
		{
			return ResourceHandleType::Window;
		}

		void Window::open()
		{
			ShowWindow(hwnd_, SW_SHOW);
			UpdateWindow(hwnd_);
		}

		void Window::update()
		{
			RedrawWindow(hwnd_, NULL, NULL, RDW_INVALIDATE);
		}

		void Window::fill_rect(int x, int y, int width, int height, int r, int g, int b)
		{
			auto brush = CreateSolidBrush(RGB(r, b, b));
			RECT rect;
			rect.left = x;
			rect.right = x + width;
			rect.top = y;
			rect.bottom = y + height;
			FillRect(mem_hdc, &rect, brush);
			DeleteObject(brush);
		}
	}
}
