// Copyright to Avram Traian. 2022 - 2022.
// File created on June 13 2022.

#include "Core/Launch/Launch.h"
#include "Editor/EditorLayer.h"

namespace Blueberry {

	class JamEdApplication : public Application
	{
	public:
		JamEdApplication(const ApplicationInfo& info)
			: Application(info)
		{
			AddLayer(bbnew EditorLayer());
		}

		virtual ~JamEdApplication() override
		{
		}
	};

	Application* CreateApplication()
	{
		ApplicationInfo info;

		info.ApplicationName = TEXT("Blueberry Editor");

		info.PrimaryWindow.Title         = TEXT("JamEd -- Windows -- 64-bit -- Renderer: Vulkan -- Untitled*");
		info.PrimaryWindow.IsPrimary     = true;
		info.PrimaryWindow.Flags         = BLUE_WINDOW_FLAG_MAXIMIZED;
		info.PrimaryWindow.EventCallback = Application::OnEvent;

		return bbnew JamEdApplication(info);
	}

}