#pragma once

#include "Base.h"

namespace Blueberry {

	class BLUEBERRY_API Application
	{
	public:
		Application();
		virtual ~Application();

	public:
		static Application* Get() { return s_Instance; }

	public:
		int32_t Run(TCHAR** cmd_params, uint32_t cmd_params_num);

	private:
		static Application* s_Instance;

	private:
		bool m_IsRunning = false;
	};

	Application* CreateApplication();

}