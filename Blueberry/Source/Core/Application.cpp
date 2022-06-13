#include "Application.h"

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
		while (true);
		return 0;
	}

}