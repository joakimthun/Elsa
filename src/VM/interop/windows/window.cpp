#include "window.h"

namespace elsa {
	namespace vm {

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

			hwnd_ = CreateWindow(
				L"ElsaWindow",
				title.c_str(),
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT,
				width, height,
				NULL,
				NULL,
				hinstance_,
				NULL
				);

			if (!hwnd_)
			{
				throw RuntimeException("Could not create window, call to CreateWindow failed");
			}
		}

		Window::~Window() 
		{

		}

		LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
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

		void Window::Open()
		{
			ShowWindow(hwnd_, SW_SHOW);
			UpdateWindow(hwnd_);
		}
	}
}
