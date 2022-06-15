#pragma once

#include "Base.h"

namespace Blueberry {

	constexpr uint64_t BLUE_SEC_TO_MILI  = 1000;
	constexpr uint64_t BLUE_SEC_TO_MICRO = 1000000;
	constexpr uint64_t BLUE_SEC_TO_NANO  = 1000000000;

	constexpr double   BLUE_MILI_TO_SEC  = 0.001;
	constexpr double   BLUE_MICRO_TO_SEC = 0.000001;
	constexpr double   BLUE_NANO_TO_SEC  = 0.000000001;

	class BLUEBERRY_API TimeStep
	{
	public:
		TimeStep()
			: m_TimeStep(0)
		{}

		TimeStep(uint64_t time_step)
			: m_TimeStep(time_step)
		{}

	public:
		float Seconds() const { return (float)(m_TimeStep * BLUE_NANO_TO_SEC); }

	private:
		uint64_t m_TimeStep;

		friend class Time;
		friend class TimePoint;
	};

	class BLUEBERRY_API TimePoint
	{
	public:
		static TimeStep Delta(TimePoint t2, TimePoint t1)
		{
			TimeStep ts;
			ts.m_TimeStep = t2.m_Time - t1.m_Time;
			return ts;
		}

	public:
		TimePoint()
			: m_Time(0)
		{}

		TimePoint(const TimePoint& other)
			: m_Time(other.m_Time)
		{}

	public:
		TimePoint& operator=(const TimePoint& other)
		{
			m_Time = other.m_Time;
			return *this;
		}

		TimeStep operator+(TimePoint time_point) const
		{
			return TimeStep(m_Time + time_point.m_Time);
		}

		TimePoint operator+(TimeStep time_step) const
		{
			return TimePoint(m_Time + time_step.m_TimeStep);
		}

		TimePoint& operator+=(TimeStep time_step)
		{
			m_Time += time_step.m_TimeStep;
			return *this;
		}

		TimeStep operator-(TimePoint time_point) const
		{
			return TimeStep(m_Time - time_point.m_Time);
		}

		TimePoint operator-(TimeStep time_step) const
		{
			return TimePoint(m_Time - time_step.m_TimeStep);
		}

		TimePoint& operator-=(TimeStep time_step)
		{
			m_Time -= time_step.m_TimeStep;
			return *this;
		}

		bool operator==(const TimePoint& other) const
		{
			return m_Time == other.m_Time;
		}

		bool operator!=(const TimePoint& other) const
		{
			return m_Time != other.m_Time;
		}

	public:
		double Seconds() const { return m_Time * BLUE_NANO_TO_SEC; }

	private:
		TimePoint(uint64_t time)
			: m_Time(time)
		{}

	private:
		uint64_t m_Time;

		friend class Time;
	};

	struct SystemTime
	{
		uint32_t Milisecond = 0;
		uint32_t Second     = 0;
		uint32_t Minute     = 0;
		uint32_t Hour       = 0;
		uint32_t Day        = 0;
		uint32_t Month      = 0;
		uint32_t Year       = 0;
	};

	class BLUEBERRY_API Time
	{
	public:
		static TimePoint GetTime();
	};

}