#include "Application.h"

#include "Launch/ExitCode.h"

#include "Platform.h"
#include "Log.h"
#include "Input.h"

#include "Time.h"

#include "Events/WindowEvents.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"

namespace Blueberry {

	Blueberry::Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationInfo& info)
		: m_Info(info)
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

		if (!Input::Initialize())
			return BLUE_EXIT_CODE_INITIALIZE_FAILED;

		Window::Create(m_Info.PrimaryWindow);

		m_IsRunning = true;

		TimePoint now = Time::GetTime();
		TimePoint last_tick = now;

		for (Layer* layer : m_Layers)
			layer->OnAttach();

		while (m_IsRunning)
		{
			TimeStep ts = now - last_tick;
			last_tick = now;
			now = Time::GetTime();

			float delta_time = ts.Seconds();

			for (Window* window : m_Windows)
				window->MessageLoop();

			for (Layer* layer : m_Layers)
				layer->Tick(delta_time);

			Input::OnUpdate();

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

					delete m_Windows[index];
					m_Windows.Remove(index);
				}
			}

			if (m_IsRunning)
				m_IsRunning = !m_Windows.IsEmpty();
		}

		m_IsRunning = false;

		for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); it--)
			(*it)->OnDetach();

		for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); it--)
			delete (*it);

		for (auto& window : m_Windows)
			delete window;
		m_Windows.Clear();

		Input::Shutdown();
		Logger::Shutdown();

		return BLUE_EXIT_CODE_SUCCESS;
	}

	void Application::AddLayer(Layer* layer)
	{
		m_Layers.Add(layer);
	}

	void Application::AddWindow(Window* window)
	{
		m_Windows.Add(window);
	}

	void Application::OnEvent(const Window* window, Event& e)
	{
		EventDispatcher dispatcher(e, window);

		dispatcher.Dispatch<WindowMinimizedEvent>([](const Window* window, const WindowMinimizedEvent& e)
			{
				Input::OnMinimized();
				return false;
			});

		dispatcher.Dispatch<KeyPressedEvent>([](const Window* window, const KeyPressedEvent& e)
			{
				Input::SetKeyPressed(e.GetKey());
				return false;
			});

		dispatcher.Dispatch<KeyReleasedEvent>([](const Window* window, const KeyReleasedEvent& e)
			{
				Input::SetKeyReleased(e.GetKey());
				return false;
			});

		dispatcher.Dispatch<MouseMovedEvent>([](const Window* window, const MouseMovedEvent& e)
			{
				Input::SetMousePosition(e.GetMouseX(), e.GetMouseY());
				return false;
			});

		dispatcher.Dispatch<MouseButtonPressedEvent>([](const Window* window, const MouseButtonPressedEvent& e)
			{
				Input::SetMouseButtonPressed(e.GetButton());
				return false;
			});

		dispatcher.Dispatch<MouseButtonReleasedEvent>([](const Window* window, const MouseButtonReleasedEvent& e)
			{
				Input::SetMouseButtonReleased(e.GetButton());
				return false;
			});

		dispatcher.Dispatch<MouseWheelScrolledEvent>([](const Window* window, const MouseWheelScrolledEvent& e)
			{
				Input::SetMouseWheelDelta(e.GetDelta());
				return false;
			});

		Vector<Layer*>& layers = Application::Get()->m_Layers;
		for (auto it = layers.rbegin(); it != layers.rend(); it--)
			(*it)->OnEvent(window, e);
	}

}