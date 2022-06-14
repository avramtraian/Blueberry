#include "Application.h"

#include "Launch/ExitCode.h"

#include "Log.h"
#include "Platform/Platform.h"

#include "Window.h"

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

		WindowData window_data;
		Window::Create(window_data);

		m_IsRunning = true;

		while (m_IsRunning)
		{
			for (auto& window : m_Windows)
			{
				window->MessageLoop();
			}

			for (int64_t index = (int64_t)m_Windows.Size() - 1; index >= 0; index--)
			{
				auto& window = m_Windows[index];

				if (window->ShouldClose())
				{
					if (window->IsPrimary())
					{
						m_IsRunning = false;
						break;
					}

					m_Windows.Remove(index);
				}
			}

			if (m_IsRunning)
				m_IsRunning = !m_Windows.IsEmpty();
		}

		m_IsRunning = false;

		m_Windows.Clear();

		Logger::Shutdown();

		return BLUE_EXIT_CODE_SUCCESS;
	}

	void Application::AddWindow(Window* window)
	{
		m_Windows.Add(window);
	}

}