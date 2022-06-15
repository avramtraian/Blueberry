#include "EditorLayer.h"

namespace Blueberry {

	EditorLayer::EditorLayer()
		: Layer(TEXT("JamEd_Layer"))
	{
	}

	EditorLayer::~EditorLayer()
	{
	}

	void EditorLayer::OnAttach()
	{
		BLUB_CORE_INFO(TEXT("EditorLayer - Successfully attached!"));
	}

	void EditorLayer::OnDetach()
	{
		BLUB_CORE_INFO(TEXT("EditorLayer - Successfully detached!"));
	}

	void EditorLayer::Tick(float delta_time)
	{
	}

	void EditorLayer::OnEvent(const class Window* window, Event& e)
	{
	}

}