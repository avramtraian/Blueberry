// Copyright to Avram Traian. 2022 - 2022.
// File created on June 14 2022.

#pragma once

#include "Base.h"
#include "Events/Event.h"

namespace Blueberry {
	
	enum WindowFlagsEnum : uint16_t
	{
		WINDOW_FLAG_None       = 0,
		WINDOW_FLAG_Fullscreen = BIT(0),
		WINDOW_FLAG_Maximized  = BIT(1),
		WINDOW_FLAG_Minimized  = BIT(2),
		WINDOW_FLAG_FixedSize  = BIT(3),
	};
	using WindowFlags = uint16_t;

	using PFN_WindowCallaback = void(*)(const class Window*, Event&);

	struct WindowSpecification
	{
		uint32_t            Width         = 400;
		uint32_t            Height        = 400;
		int32_t             PositionX     = 100;
		int32_t             PositionY     = 100;
		String              Title         = TEXT("Blueberry Window");
		bool                IsPrimary     = false;
		WindowFlags         Flags         = WINDOW_FLAG_None;
		PFN_WindowCallaback EventCallback = nullptr;
	};

	enum WindowErrorCodesEnum : uint16_t
	{
		WINDOW_ERROR_CODE_None                    = 0x00,
		WINDOW_ERROR_CODE_Unknown                 = 0x01,
		WINDOW_ERROR_CODE_InvalidFlagsCombination = 0x02,
	};
	using WindowErrorCode = uint16_t;

	class BLUEBERRY_API Window
	{
	public:
		static Window* Create(const WindowSpecification& spec);

		~Window();

		Window(const Window&) = delete;
		Window(Window&&) noexcept = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) noexcept = delete;

	public:
		WindowSpecification& GetData() { return m_Specification; }

		const WindowSpecification& GetData() const { return m_Specification; }

		void* GetNativeHandle() const { return m_NativeHandle; }

		bool IsPrimary() const { return m_Specification.IsPrimary; }

		bool ShouldClose() const { return m_ShouldClose; }

		void ScheduleClose() { m_ShouldClose = true; }

		WindowErrorCode GetErrorCode() const { return m_ErrorCode; }

	public:
		void SetTitle(StringView title);

		void SetSize(uint32_t width, uint32_t height);

		void SetPosition(int32_t x_pos, int32_t y_pos);

		void Minimize();

		void Maximize();

		void ProcessMessages();

	private:
		Window(const WindowSpecification& data);

	private:
		WindowSpecification m_Specification;

		void* m_NativeHandle;

		bool m_ShouldClose = false;

		WindowErrorCode m_ErrorCode = WINDOW_ERROR_CODE_None;
	};

}