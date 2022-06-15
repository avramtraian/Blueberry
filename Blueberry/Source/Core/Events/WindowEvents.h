#pragma once

#include "Event.h"

namespace Blueberry {

	class BLUEBERRY_API WindowResizedEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::WindowResized; }

	public:
		WindowResizedEvent(uint32_t width, uint32_t height)
			: Event(GetStaticType())
			, m_Width(width)
			, m_Height(height)
		{}

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

	private:
		uint32_t m_Width, m_Height;
	};

	class BLUEBERRY_API WindowMinimizedEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::WindowMinimized; }

	public:
		WindowMinimizedEvent()
			: Event(GetStaticType())
		{}
	};

	class BLUEBERRY_API WindowMovedEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::WindowMoved; }

	public:
		WindowMovedEvent(int32_t pos_x, int32_t pos_y)
			: Event(GetStaticType())
			, m_PositionX(pos_x)
			, m_PositionY(pos_y)
		{}

		int32_t GetPositionX() const { return m_PositionX; }
		int32_t GetPositionY() const { return m_PositionY; }

	private:
		int32_t m_PositionX, m_PositionY;
	};

	class BLUEBERRY_API WindowTitleChangedEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::WindowTitleChanged; }

	public:
		WindowTitleChangedEvent(StringView title)
			: Event(GetStaticType())
			, m_Title(title)
		{}

		StringView GetTitle() const { return m_Title; }

	private:
		StringView m_Title;
	};

	class BLUEBERRY_API WindowClosedEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::WindowClosed; }

	public:
		WindowClosedEvent()
			: Event(GetStaticType())
		{}
	};

}