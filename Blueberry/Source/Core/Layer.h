#pragma once

#include "Base.h"
#include "Events/Event.h"

namespace Blueberry {

	class BLUEBERRY_API Layer
	{
	public:
		Layer(StringView layer_name)
			: m_LayerName(layer_name.CStr())
		{}

		virtual ~Layer() = default;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;

		virtual void Tick(float delta_time) = 0;

		virtual void OnEvent(const class Window* window, Event& e) = 0;

	private:
		const TCHAR* m_LayerName;
	};

}