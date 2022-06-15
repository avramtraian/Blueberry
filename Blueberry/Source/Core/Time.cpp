#include "Time.h"

#include "Platform.h"

namespace Blueberry {

	TimePoint Time::GetTime()
	{
		uint64_t performance_count = Platform::GetPerformanceCount() - Platform::GetStartupPerformanceCount();
		uint64_t performance_frequency = Platform::GetPerformanceFrequency();

		uint64_t whole_seconds = performance_count / performance_frequency;
		uint64_t remained_ticks = performance_count - (whole_seconds * performance_frequency);

		TimePoint time;
		time.m_Time = whole_seconds * BLUE_SEC_TO_NANO + (remained_ticks * BLUE_SEC_TO_NANO) / performance_frequency;
		return time;
	}

}