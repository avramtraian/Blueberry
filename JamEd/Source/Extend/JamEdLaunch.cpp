// Copyright to Avram Traian. 2022 - 2022.
// File created on June 13 2022.

#include "Core/Launch/Launch.h"
#include "Editor/EditorLayer.h"

namespace Blueberry {

	class JamEdApplication : public Application
	{
	public:
		JamEdApplication(const ApplicationSpecification& spec)
			: Application(spec)
		{
			AddLayer(bbnew EditorLayer());
		}

		virtual ~JamEdApplication() override
		{
		}
	};

	Application* CreateApplication(const CommandLineArguments& command_args)
	{
		ApplicationSpecification spec;
		spec.Name = TEXT("Blueberry Editor");
		spec.WindowTitle = TEXT("JamEd -- Windows -- 64-bit -- Renderer: Vulkan -- Untitled*");
		spec.CommandLineArgs = command_args;

		return bbnew JamEdApplication(spec);
	}

}