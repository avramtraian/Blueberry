// Copyright to Avram Traian. 2022 - 2022.
// File created on June 15 2022.

#pragma once

#include "Event.h"
#include "Core/KeyCodes.h"

namespace Blueberry {

	class BLUEBERRY_API KeyPressedEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::KeyPressed; }

	public:
		KeyPressedEvent(Key key)
			: Event(GetStaticType())
			, m_Key(key)
		{}

		Key GetKey() const { return m_Key; }

	private:
		Key m_Key;
	};

	class BLUEBERRY_API KeyReleasedEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::KeyReleased; }

	public:
		KeyReleasedEvent(Key key)
			: Event(GetStaticType())
			, m_Key(key)
		{}

		Key GetKey() const { return m_Key; }

	private:
		Key m_Key;
	};

}