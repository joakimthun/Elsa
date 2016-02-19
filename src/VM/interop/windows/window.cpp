#include "window.h"

namespace elsa {
	namespace vm {

		std::vector<Renderable> render_queue;

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
			case WM_PAINT: {
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				for (const auto& r : render_queue)
				{
					FillRect(hdc, &r.rect, r.brush);
					DeleteObject(r.brush);
				}
				EndPaint(hWnd, &ps);
				render_queue.clear();
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

		void Window::fill_rect(int x, int y, int width, int height)
		{
			Renderable r;
			r.brush = CreateSolidBrush(RGB(50, 151, 151));
			r.rect.left = x;
			r.rect.right = x + width;
			r.rect.top = y;
			r.rect.bottom = y + height;
			render_queue.push_back(r);
		}
	}
}
