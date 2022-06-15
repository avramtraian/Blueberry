#if BLUE_PLATFORM_WINDOWS

#include "Core/Platform/Platform.h"

#include "WindowsHeaders.h"

#include <cstdlib>

namespace Blueberry {

	struct WindowsPlatformData
	{
		HANDLE   ConsoleHandle           = INVALID_HANDLE_VALUE;
		bool     ConsoleIsAttached       = false;
		uint32_t ConsoleFlags            = 0;

		uint64_t PerformanceFrequency    = 0;
		uint64_t StartupPerformanceCount = 0;
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

		LARGE_INTEGER performance_frequency;
		QueryPerformanceFrequency(&performance_frequency);
		s_PlatformData->PerformanceFrequency = performance_frequency.QuadPart;

		LARGE_INTEGER performance_count;
		QueryPerformanceCounter(&performance_count);
		s_PlatformData->StartupPerformanceCount = performance_count.QuadPart;

#if !BLUE_BUILD_SHIPPING
		s_PlatformData->ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		if (s_PlatformData->ConsoleHandle == INVALID_HANDLE_VALUE)
			return false;

		s_PlatformData->ConsoleIsAttached = true;
		SetConsoleFlags(BLUE_CONSOLE_FLAG_BLACK_BACKGROUND | BLUE_CONSOLE_FLAG_WHITE_TEXT);
#endif

		return true;
	}

	void Platform::Shutdown()
	{
		if (!s_PlatformData)
			return;

#if !BLUE_BUILD_SHIPPING
		SetConsoleFlags(BLUE_CONSOLE_FLAG_BLACK_BACKGROUND | BLUE_CONSOLE_FLAG_WHITE_TEXT);
#endif

		s_PlatformData->~WindowsPlatformData();
		free(s_PlatformData);
		s_PlatformData = nullptr;
	}

	void* Platform::Allocate(SizeT block_size)
	{
		return malloc((size_t)block_size);
	}

	void Platform::Free(void* memory_block)
	{
		free(memory_block);
	}

	void Platform::SleepFor(double sleep_time_mili)
	{
		Sleep((DWORD)sleep_time_mili);
	}

	uint64_t Platform::GetPerformanceCount()
	{
		LARGE_INTEGER performance_counter;
		QueryPerformanceCounter(&performance_counter);
		return performance_counter.QuadPart;
	}

	uint64_t Platform::GetPerformanceFrequency()
	{
		return s_PlatformData->PerformanceFrequency;
	}

	uint64_t Platform::GetStartupPerformanceCount()
	{
		return s_PlatformData->StartupPerformanceCount;
	}

	void Platform::GetLocalSystemTime(SystemTime& out_local_time)
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

	void Platform::SetConsoleFlags(uint32_t flags)
	{
		if (!s_PlatformData->ConsoleIsAttached)
			return;

		if (s_PlatformData->ConsoleFlags == flags)
			return;

		SetConsoleTextAttribute(s_PlatformData->ConsoleHandle, (WORD)flags);
		s_PlatformData->ConsoleFlags = flags;
	}

	uint32_t Platform::GetConsoleFlags()
	{
		return s_PlatformData->ConsoleFlags;
	}

	void Platform::WriteToConsole(StringView message)
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