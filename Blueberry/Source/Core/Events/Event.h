#pragma once

#include "Core/Base.h"

namespace Blueberry {

	enum class EventType : uint8_t
	{
		None = 0,

		WindowMoved,
		WindowResized,
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
		EventDispatcher(Event& e)
			: m_Event(e)
		{}

		template<typename T>
		void Dispatch(bool(*pfn_event_callback)(const T&))
		{
			if (T::GetStaticType() == m_Event.GetType() && !m_Event.m_Handled)
				m_Event.m_Handled = pfn_event_callback(*(static_cast<const T*>(&m_Event)));
		}

	private:
		Event& m_Event;
	};

}