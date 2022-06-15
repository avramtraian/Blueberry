#if BLUE_PLATFORM_WINDOWS

#include "Core/Window.h"
#include "Core/Application.h"

#include "Core/Events/WindowEvents.h"
#include "Core/Events/MouseEvents.h"
#include "Core/Events/KeyboardEvents.h"

#include "WindowsHeaders.h"

namespace Blueberry {

	Window* Window::Create(const WindowData& data)
	{
		return new Window(data);
	}

	static LRESULT BlueberryWindowProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	namespace Utils {

		static HINSTANCE s_ProcessHandle = 0;

		constexpr const TCHAR* BLUE_WINDOW_CLASS_NAME = TEXT("__Blueberry_Window_Class__");

		static void RegisterWindowClass()
		{
			s_ProcessHandle = GetModuleHandle(NULL);

			WNDCLASSEX wnd_class = {};

			wnd_class.hInstance   = s_ProcessHandle;
			wnd_class.lpfnWndProc = Blueberry::BlueberryWindowProcedure;
			wnd_class.hIcon       = NULL;
			wnd_class.hIconSm     = NULL;

			wnd_class.lpszClassName = BLUE_WINDOW_CLASS_NAME;
			wnd_class.cbSize = sizeof(WNDCLASSEX);
			wnd_class.hCursor = NULL;
			wnd_class.hbrBackground = NULL;
			wnd_class.cbWndExtra = 0;
			wnd_class.cbClsExtra = 0;
			wnd_class.lpszMenuName = NULL;
			wnd_class.style = 0;

			RegisterClassEx(&wnd_class);
		}

		static bool ValidateWindowFlags(WindowFlags flags)
		{
			return true;
		}

		static void TranslateWindowFlags(WindowFlags flags, DWORD& out_style_flags, DWORD& out_ex_style_flags, int& out_show_mode)
		{
			out_ex_style_flags = 0;

			if (flags & BLUE_WINDOW_FLAG_FULLSCREEN)
			{
				out_style_flags = WS_POPUP | WS_MAXIMIZE;
				out_show_mode = SW_SHOWMAXIMIZED;
			}
			else
			{
				out_style_flags = WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
				out_show_mode = SW_SHOW;

				if (!(flags & BLUE_WINDOW_FLAG_FIXED_SIZE))
				{
					out_style_flags |= WS_THICKFRAME | WS_MAXIMIZEBOX;
				}
				if (flags & BLUE_WINDOW_FLAG_MAXIMIZED)
				{
					out_style_flags |= WS_MAXIMIZE;
					out_show_mode = SW_SHOWMAXIMIZED;
				}
				if (flags & BLUE_WINDOW_FLAG_MINIMIZED)
				{
					out_style_flags |= WS_MINIMIZE;
					out_show_mode = SW_SHOWMINIMIZED;
				}
			}
		}

		static Window* s_CreatingWindow = nullptr;

		static Window* FindWindowByHWND(HWND window_hwnd)
		{
			auto& windows = Application::Get()->GetWindows();
			for (auto& window : windows)
			{
				if (window->GetNativeHandle() == (void*)window_hwnd)
					return window;
			}

			return s_CreatingWindow;
		}

	}

	Window::Window(const WindowData& data)
		: m_Data(data)
		, m_NativeHandle(nullptr)
	{
		// First time a window is created, the window class is registered
		static bool registered_window_class = false;
		if (!registered_window_class)
		{
			Utils::RegisterWindowClass();
			registered_window_class = true;
		}

		if (!Utils::ValidateWindowFlags(m_Data.Flags))
		{
			m_ErrorCode = BLUE_WINDOW_ERROR_CODE_INVALID_FLAGS_COMBINATION;
			BLUB_CORE_ERROR(TEXT("Invalid combination of window flags!"));
			return;
		}

		DWORD style_flags;
		DWORD ex_style_flags;
		int show_mode;

		Utils::TranslateWindowFlags(m_Data.Flags, style_flags, ex_style_flags, show_mode);

		int width  = m_Data.Width;
		int height = m_Data.Height;
		int x_pos  = m_Data.PositionX;
		int y_pos  = m_Data.PositionY;

		Utils::s_CreatingWindow = this;

		HWND window_hwnd = CreateWindowEx(
			ex_style_flags, Utils::BLUE_WINDOW_CLASS_NAME,
			m_Data.Title.CStr(),
			style_flags,
			x_pos, y_pos, width, height,
			NULL, NULL, Utils::s_ProcessHandle, NULL);

		Utils::s_CreatingWindow = nullptr;

		if (window_hwnd == NULL)
		{
			m_ErrorCode = BLUE_WINDOW_ERROR_CODE_UNKNOWN;
			BLUB_CORE_ERROR(TEXT("Window creation failed!"));
			return;
		}

		m_NativeHandle = window_hwnd;
		Application::Get()->AddWindow(this);

		ShowWindow(window_hwnd, show_mode);
	}

	Window::~Window()
	{
		DestroyWindow((HWND)m_NativeHandle);
	}

	void Window::SetTitle(StringView title)
	{
		m_Data.Title = title;
		SetWindowText((HWND)m_NativeHandle, title.CStr());

		WindowTitleChangedEvent e(m_Data.Title);
		m_Data.EventCallback(this, e);
	}

	void Window::SetSize(uint32_t width, uint32_t height)
	{
		SetWindowPos((HWND)m_NativeHandle, HWND_TOP, 0, 0, width, height, SWP_NOMOVE);
	}

	void Window::SetPosition(int32_t x_pos, int32_t y_pos)
	{
		SetWindowPos((HWND)m_NativeHandle, HWND_TOP, x_pos, y_pos, 0, 0, SWP_NOSIZE);
	}

	void Window::Minimize()
	{
		ShowWindow((HWND)m_NativeHandle, SW_SHOWMINIMIZED);
	}

	void Window::Maximize()
	{
		ShowWindow((HWND)m_NativeHandle, SW_SHOWMAXIMIZED);
	}

	void Window::MessageLoop()
	{
		MSG window_msg;
		while (PeekMessage(&window_msg, (HWND)m_NativeHandle, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&window_msg);
			DispatchMessage(&window_msg);
		}
	}

	LRESULT BlueberryWindowProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		switch (Msg)
		{
			case WM_MOUSEMOVE:
			{
				POINTS pos = MAKEPOINTS(lParam);

				Window* window = Utils::FindWindowByHWND(hWnd);

				MouseMovedEvent e((int32_t)pos.x, (int32_t)pos.y);
				window->GetData().EventCallback(window, e);

				return 0;
			}

			case WM_LBUTTONDOWN:
			{
				Window* window = Utils::FindWindowByHWND(hWnd);

				MouseButtonPressedEvent e(MouseButton::Left);
				window->GetData().EventCallback(window, e);

				return 0;
			}
			case WM_LBUTTONUP:
			{
				Window* window = Utils::FindWindowByHWND(hWnd);

				MouseButtonReleasedEvent e(MouseButton::Left);
				window->GetData().EventCallback(window, e);

				return 0;
			}

			case WM_RBUTTONDOWN:
			{
				Window* window = Utils::FindWindowByHWND(hWnd);

				MouseButtonPressedEvent e(MouseButton::Right);
				window->GetData().EventCallback(window, e);

				return 0;
			}
			case WM_RBUTTONUP:
			{
				Window* window = Utils::FindWindowByHWND(hWnd);

				MouseButtonReleasedEvent e(MouseButton::Right);
				window->GetData().EventCallback(window, e);

				return 0;
			}

			case WM_MBUTTONDOWN:
			{
				Window* window = Utils::FindWindowByHWND(hWnd);

				MouseButtonPressedEvent e(MouseButton::Middle);
				window->GetData().EventCallback(window, e);

				return 0;
			}
			case WM_MBUTTONUP:
			{
				Window* window = Utils::FindWindowByHWND(hWnd);

				MouseButtonReleasedEvent e(MouseButton::Middle);
				window->GetData().EventCallback(window, e);

				return 0;
			}

			case WM_MOUSEWHEEL:
			{
				auto delta = GET_WHEEL_DELTA_WPARAM(wParam);

				Window* window = Utils::FindWindowByHWND(hWnd);

				MouseWheelScrolledEvent e(delta > 0 ? 1 : -1);
				window->GetData().EventCallback(window, e);

				return 0;
			}

			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			{
				Key key = (Key)wParam;

				Window* window = Utils::FindWindowByHWND(hWnd);

				KeyPressedEvent e(key);
				window->GetData().EventCallback(window, e);

				return 0;
			}
			case WM_KEYUP:
			case WM_SYSKEYUP:
			{
				Key key = (Key)wParam;

				Window* window = Utils::FindWindowByHWND(hWnd);

				KeyReleasedEvent e(key);
				window->GetData().EventCallback(window, e);

				return 0;
			}

			case WM_SIZE:
			{
				uint32_t width  = (uint32_t)(LOWORD(lParam));
				uint32_t height = (uint32_t)(HIWORD(lParam));

				Window* window = Utils::FindWindowByHWND(hWnd);
				window->GetData().Width  = width;
				window->GetData().Height = height;
				
				WindowResizedEvent e(width, height);
				window->GetData().EventCallback(window, e);

				return 0;
			}

			case WM_MOVE:
			{
				POINTS pos = MAKEPOINTS(lParam);

				Window* window = Utils::FindWindowByHWND(hWnd);
				window->GetData().PositionX = (int32_t)pos.x;
				window->GetData().PositionY = (int32_t)pos.y;

				WindowMovedEvent e((int32_t)pos.x, (int32_t)pos.y);
				window->GetData().EventCallback(window, e);

				return 0;
			}

			case WM_CLOSE:
			{
				Window* window = Utils::FindWindowByHWND(hWnd);
				window->ScheduleClose();

				WindowClosedEvent e;
				window->GetData().EventCallback(window, e);

				return 0;
			}
		}
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

}

#endif