#if BLUE_PLATFORM_WINDOWS

#include "Core/Platform/Platform.h"

#include "WindowsHeaders.h"

#include <cstdlib>

namespace Blueberry {

	struct WindowsPlatformData
	{
		HANDLE   ConsoleHandle     = INVALID_HANDLE_VALUE;
		bool     ConsoleIsAttached = false;
		uint32_t ConsoleFlags      = 0;
	};
	static WindowsPlatformData* s_PlatformData = nullptr;

	bool Platform::Initialize()
	{
		if (s_PlatformData)
			return false;

		s_PlatformData = (WindowsPlatformData*)malloc(sizeof(WindowsPlatformData));
		if (!s_PlatformData)
			return false;
		new (s_PlatformData) WindowsPlatformData();

#if !BLUE_BUILD_SHIPPING
		s_PlatformData->ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		if (s_PlatformData->ConsoleHandle == INVALID_HANDLE_VALUE)
			return false;

		s_PlatformData->ConsoleIsAttached = true;
		ConsoleSetFlags(BLUE_CONSOLE_FLAG_BLACK_BACKGROUND | BLUE_CONSOLE_FLAG_WHITE_TEXT);
#endif

		return true;
	}

	void Platform::Shutdown()
	{
		if (!s_PlatformData)
			return;

#if !BLUE_BUILD_SHIPPING
		ConsoleSetFlags(BLUE_CONSOLE_FLAG_BLACK_BACKGROUND | BLUE_CONSOLE_FLAG_WHITE_TEXT);
#endif

		s_PlatformData->~WindowsPlatformData();
		free(s_PlatformData);
		s_PlatformData = nullptr;
	}

	void* Platform::MemoryAllocate(SizeT block_size)
	{
		return malloc((size_t)block_size);
	}

	void Platform::MemoryFree(void* memory_block)
	{
		free(memory_block);
	}

	void Platform::TimeGetLocalTime(SystemTime& out_local_time)
	{
		SYSTEMTIME local_time;
		GetLocalTime(&local_time);

		out_local_time.Milisecond = local_time.wMilliseconds;
		out_local_time.Second = local_time.wSecond;
		out_local_time.Minute = local_time.wMinute;
		out_local_time.Hour = local_time.wHour;
		out_local_time.Day = local_time.wDay;
		out_local_time.Month = local_time.wMonth;
		out_local_time.Year = local_time.wYear;
	}

	void Platform::ConsoleSetFlags(uint32_t flags)
	{
		if (!s_PlatformData->ConsoleIsAttached)
			return;

		if (s_PlatformData->ConsoleFlags == flags)
			return;

		SetConsoleTextAttribute(s_PlatformData->ConsoleHandle, (WORD)flags);
		s_PlatformData->ConsoleFlags = flags;
	}

	uint32_t Platform::ConsoleGetFlags()
	{
		return s_PlatformData->ConsoleFlags;
	}

	void Platform::ConsoleWrite(StringView message)
	{
		if (!s_PlatformData->ConsoleIsAttached)
			return;

		if (WriteConsole(s_PlatformData->ConsoleHandle, message.CStr(), (DWORD)message.Length(), NULL, NULL) == 0)
		{
			// TODO (Avr): Assert
		}
	}

}

#endif