#pragma once

#include "CoreMinimal.h"

#include "Layer.h"
#include "Window.h"
#include "Events/Event.h"

namespace Blueberry {

	struct ApplicationInfo
	{
		const TCHAR* ApplicationName;

		WindowData   PrimaryWindow;
	};

	class BLUEBERRY_API Application
	{
	public:
		Application(const ApplicationInfo& info);
		virtual ~Application();

	public:
		static Application* Get() { return s_Instance; }

		static void OnEvent(const Window* window, Event& e);

	public:
		int32_t Run(TCHAR** cmd_params, uint32_t cmd_params_num);

		void AddLayer(Layer* layer);

		const Vector<Window*>& GetWindows() const { return m_Windows; }

		void AddWindow(Window* window);

	private:
		static Application* s_Instance;

	private:
		ApplicationInfo m_Info;

		bool m_IsRunning = false;

		Vector<Layer*> m_Layers;

		Vector<Window*> m_Windows;
	};

	Application* CreateApplication();

}