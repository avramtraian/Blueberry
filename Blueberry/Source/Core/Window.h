#pragma once

#include "Base.h"

namespace Blueberry {
	
	enum WindowFlagsEnum : uint16_t
	{
		BLUE_WINDOW_FLAG_NONE       = 0,
		BLUE_WINDOW_FLAG_FULLSCREEN = 1 << 0,
		BLUE_WINDOW_FLAG_MAXIMIZED  = 1 << 1,
		BLUE_WINDOW_FLAG_MINIMIZED  = 1 << 2,
		BLUE_WINDOW_FLAG_FIXED_SIZE = 1 << 3,
	};
	using WindowFlags = uint16_t;

	struct WindowData
	{
		uint32_t    Width     = 400;
		uint32_t    Height    = 400;
		int32_t     PositionX = 100;
		int32_t     PositionY = 100;
		String      Title     = TEXT("Blueberry Window");
		bool        IsPrimary = false;
		WindowFlags Flags     = BLUE_WINDOW_FLAG_NONE;
	};

	enum WindowErrorCodesEnum : uint16_t
	{
		BLUE_WINDOW_ERROR_CODE_NONE                      = 0,
		BLUE_WINDOW_ERROR_CODE_UNKNOWN                   = 1,
		BLUE_WINDOW_ERROR_CODE_INVALID_FLAGS_COMBINATION = 2,
	};
	using WindowErrorCode = uint16_t;

	class BLUEBERRY_API Window
	{
	public:
		static Window* Create(const WindowData& data);

		~Window();

		Window(const Window&) = delete;
		Window(Window&&) noexcept = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) noexcept = delete;

	public:
		const WindowData& GetData() const { return m_Data; }

		void* GetNativeHandle() const { return m_NativeHandle; }

		bool IsPrimary() const { return m_Data.IsPrimary; }

		bool ShouldClose() const { return m_ShouldClose; }

		void ScheduleClose() { m_ShouldClose = true; }

		WindowErrorCode GetErrorCode() const { return m_ErrorCode; }

	public:
		void SetTitle(StringView title);

		void SetSize(uint32_t width, uint32_t height);

		void SetPosition(int32_t x_pos, int32_t y_pos);

		void Minimize();

		void Maximize();

		void MessageLoop();

	private:
		Window(const WindowData& data);

	private:
		WindowData m_Data;

		void* m_NativeHandle;

		bool m_ShouldClose = false;

		WindowErrorCode m_ErrorCode = BLUE_WINDOW_ERROR_CODE_NONE;
	};

}