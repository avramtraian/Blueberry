#if BLUE_PLATFORM_WINDOWS

#include "Core/Window.h"

#include "WindowsHeaders.h"

namespace Blueberry {

	Window* Window::Create(const WindowData& data)
	{
		return new Window(data);
	}

	static LRESULT WindowProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	namespace Utils {

		constexpr const TCHAR* BLUE_WINDOW_CLASS_NAME = TEXT("__Blueberry_Window_Class__");

		static void RegisterWindowClass()
		{
			WNDCLASSEX wnd_class = {};

			wnd_class.hInstance   = GetModuleHandle(NULL);
			wnd_class.lpfnWndProc = WindowProcedure;
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

		HWND window_hwnd = CreateWindowEx(
			ex_style_flags, Utils::BLUE_WINDOW_CLASS_NAME,
			m_Data.Title.CStr(),
			style_flags,
			x_pos, y_pos, width, height,
			NULL, NULL, GetModuleHandle(NULL), NULL);

		if (window_hwnd == NULL)
		{
			m_ErrorCode = BLUE_WINDOW_ERROR_CODE_UNKNOWN;
			BLUB_CORE_ERROR(TEXT("Window creation failed!"));
			return;
		}

		m_NativeHandle = window_hwnd;
		ShowWindow(window_hwnd, show_mode);
	}

	Window::~Window()
	{
		DestroyWindow((HWND)m_NativeHandle);
	}

	void Window::SetTitle(StringView title)
	{
		SetWindowText((HWND)m_NativeHandle, title.CStr());
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

	LRESULT WindowProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		switch (Msg)
		{
			case WM_CLOSE:
			{
				return 0;
			}
		}
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

}

#endif