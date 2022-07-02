// Copyright to Avram Traian. 2022 - 2022.
// File created on June 15 2022.

#pragma once

#include "Core/Base.h"

namespace Blueberry {

	enum class EventType : uint8_t
	{
		None = 0,

		WindowResized,
		WindowMoved,
		WindowMinimized,
		WindowTitleChanged,
		WindowClosed,

		MouseMoved,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseWheelScrolled,

		KeyPressed,
		KeyReleased
	};

	class BLUEBERRY_API Event
	{
	public:
		Event(EventType type)
			: m_Type(type)
			, m_Handled(false)
		{}

		EventType GetType() const { return m_Type; }

	private:
		EventType m_Type;
		bool m_Handled;
		
		friend class EventDispatcher;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e, const class Window* window)
			: m_Event(e)
			, m_Window(window)
		{}

		template<typename T>
		void Dispatch(bool(*pfn_event_callback)(const class Window*, const T&))
		{
			if (T::GetStaticType() == m_Event.GetType() && !m_Event.m_Handled)
				m_Event.m_Handled = pfn_event_callback(m_Window , *(static_cast<const T*>(&m_Event)));
		}

	private:
		Event& m_Event;
		const class Window* m_Window;
	};

}