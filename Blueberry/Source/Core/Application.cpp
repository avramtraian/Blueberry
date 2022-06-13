#include "Application.h"

#include "Launch/ExitCode.h"

#include "Log.h"
#include "Platform/Platform.h"

namespace Blueberry {

	Blueberry::Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		if (s_Instance)
		{
			return;
		}

		s_Instance = this;
	}

	Application::~Application()
	{
		if (s_Instance != this)
		{
			return;
		}

		s_Instance = nullptr;
	}

	int32_t Application::Run(TCHAR** cmd_params, uint32_t cmd_params_num)
	{
		if (!Logger::Initialize())
			return BLUE_EXIT_CODE_INITIALIZE_FAILED;

		float delta_time = 0.0f;

		// Sets the 'm_IsRunning' flag to true
		m_IsRunning = true;

		while (m_IsRunning)
		{
		}

		// Ensure that 'm_IsRunning' is set to false
		m_IsRunning = false;

		Logger::Shutdown();

		return BLUE_EXIT_CODE_SUCCESS;
	}

}