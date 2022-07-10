// Copyright to Avram Traian. 2022 - 2022.
// File created on June 15 2022.

#pragma once

#include "Core/CoreMinimal.h"
#include "Core/Layer.h"

namespace Blueberry {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() override;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void Tick(float delta_time) override;

		virtual void OnEvent(const class Window* window, Event& e) override;
	};

}