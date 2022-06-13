#pragma once

#include "Core/Base.h"

#include "Core/Platform/Windows/WindowsHeaders.h"

#if BLUE_BUILD_SHIPPING

	INT WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
	{
		return (INT)Blueberry::BlueberryMain((TCHAR**)__wargv, (uint32_t)__argc);
	}

#else
	
	int wmain(int cmd_params_num, wchar_t** cmd_params)
	{
		return (int)Blueberry::BlueberryMain((TCHAR**)cmd_params, (uint32_t)cmd_params_num);
	}

#endif