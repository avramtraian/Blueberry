// Copyright to Avram Traian. 2022 - 2022.
// File created on June 13 2022.

#pragma once

#include "ExitCode.h"

#include "Core/Base.h"
#include "Core/Application.h"
#include "Core/Platform.h"
#include "Core/Memory.h"
#include "Core/Log.h"
#include "Core/Filesystem/Filesystem.h"

namespace Blueberry {
	
	static bool s_RestartApplication = false;

	inline int32_t BlueberryMain(CharT** cmd_params, uint32_t cmd_params_count)
	{
		CommandLineArguments command_args;
		command_args.Arguments = cmd_params;
		command_args.Count = cmd_params_count;

		if (!Platform::Initialize())
			return BLUE_EXIT_CODE_INITIALIZE_FAILED;

		if (!Memory::Initialize(command_args))
			return BLUE_EXIT_CODE_INITIALIZE_FAILED;

		if (!Logger::Initialize())
			return BLUE_EXIT_CODE_INITIALIZE_FAILED;

		if (!Filesystem::Initialize())
			return BLUE_EXIT_CODE_INITIALIZE_FAILED;

		int32_t return_code = BLUE_EXIT_CODE_SUCCESS;

		do
		{
			// Creates the application
			Application* application = CreateApplication(command_args);

			// Runs the application
			return_code = application->Run(cmd_params, cmd_params_count);

			// Destroys the application
			delete application;
		}
		while (s_RestartApplication);

		Filesystem::Shutdown();
		Logger::Shutdown();
		Memory::Shutdown();
		Platform::Shutdown();

		return return_code;
	}

}

#if BLUE_PLATFORM_WINDOWS // Compiling for Windows
	#include "WindowsLaunch.h"
#endif