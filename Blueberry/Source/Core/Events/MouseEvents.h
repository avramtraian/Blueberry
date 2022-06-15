#pragma once

#include "Event.h"
#include "Core/KeyCodes.h"

namespace Blueberry {

	class BLUEBERRY_API MouseMovedEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::MouseMoved; }

	public:
		MouseMovedEvent(int32_t mouse_x, int32_t mouse_y)
			: Event(GetStaticType())
			, m_MouseX(mouse_x)
			, m_MouseY(mouse_y)
		{}

		int32_t GetMouseX() const { return m_MouseY; }
		int32_t GetMouseY() const { return m_MouseY; }

	private:
		int32_t m_MouseX, m_MouseY;
	};

	class BLUEBERRY_API MouseButtonPressedEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::MouseButtonPressed; }

	public:
		MouseButtonPressedEvent(MouseButton button)
			: Event(GetStaticType())
			, m_Button(button)
		{}

		MouseButton GetButton() const { return m_Button; }

	private:
		MouseButton m_Button;
	};

	class BLUEBERRY_API MouseButtonReleasedEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::MouseButtonReleased; }

	public:
		MouseButtonReleasedEvent(MouseButton button)
			: Event(GetStaticType())
			, m_Button(button)
		{}

		MouseButton GetButton() const { return m_Button; }

	private:
		MouseButton m_Button;
	};

	class BLUEBERRY_API MouseWheelScrolledEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::MouseWheelScrolled; }

	public:
		MouseWheelScrolledEvent(double delta)
			: Event(GetStaticType())
			, m_Delta(delta)
		{}

		double GetDelta() const { return m_Delta; }

	private:
		double m_Delta;
	};

}