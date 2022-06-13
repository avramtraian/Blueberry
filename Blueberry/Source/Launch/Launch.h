#pragma once

#include "Core/Application.h"

namespace Blueberry {
	
	static bool s_RestartApplication = false;

	inline int32_t BlueberryMain(TCHAR** cmd_params, uint32_t cmd_params_num)
	{
		int32_t return_code = 0;

		do
		{
			// Creates the application
			Application* application = CreateApplication();

			// Runs the application
			return_code = application->Run(cmd_params, cmd_params_num);

			// Destroys the application
			delete application;
		}
		while (s_RestartApplication);

		return return_code;
	}

}

#if BLUE_PLATFORM_WINDOWS // Compiling for Windows
	#include "WindowsLaunch.h"
#endif