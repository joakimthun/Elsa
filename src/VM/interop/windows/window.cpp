#include "window.h"

namespace elsa {
	namespace vm {

		Window::Window() 
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
				L"ElsaWindow",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT,
				800, 600,
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
			PAINTSTRUCT ps;
			HDC hdc;
			//TCHAR greeting[] = _T("Hello, World!");

			switch (message)
			{
			case WM_PAINT:
				hdc = BeginPaint(hWnd, &ps);

				// Here your application is laid out.
				// For this introduction, we just print out "Hello, World!"
				// in the top left corner.
				//TextOut(hdc,
				//	5, 5,
				//	greeting, _tcslen(greeting));
				// End application-specific layout section.

				EndPaint(hWnd, &ps);
				break;
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

			//// Main message loop:
			//MSG msg;
			//while (GetMessage(&msg, NULL, 0, 0))
			//{
			//	TranslateMessage(&msg);
			//	DispatchMessage(&msg);
			//}
		}
	}
}
