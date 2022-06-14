#pragma once

#include "CoreMinimal.h"

namespace Blueberry {

	class Window;

	class BLUEBERRY_API Application
	{
	public:
		Application();
		virtual ~Application();

	public:
		static Application* Get() { return s_Instance; }

	public:
		int32_t Run(TCHAR** cmd_params, uint32_t cmd_params_num);

		const Vector<Window*>& GetWindows() const { return m_Windows; }

		void AddWindow(Window* window);

	private:
		static Application* s_Instance;

	private:
		bool m_IsRunning = false;

		Vector<Window*> m_Windows;
	};

	Application* CreateApplication();

}