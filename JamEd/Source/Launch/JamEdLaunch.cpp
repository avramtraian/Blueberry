#include "Launch/Launch.h"

namespace Blueberry {

	class JamEdApplication : public Application
	{
	public:
		JamEdApplication(const ApplicationInfo& info)
			: Application(info)
		{
		}

		virtual ~JamEdApplication() override
		{
		}
	};

	Application* CreateApplication()
	{
		ApplicationInfo info;
		info.ApplicationName = TEXT("Blueberry Editor");
		info.PrimaryWindow.Title     = TEXT("JamEd -- Windows -- 64-bit -- Renderer: Vulkan -- Untitled*");
		info.PrimaryWindow.IsPrimary = true;
		info.PrimaryWindow.Flags     = BLUE_WINDOW_FLAG_MAXIMIZED;

		return new JamEdApplication(info);
	}

}