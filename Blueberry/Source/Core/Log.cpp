// Copyright to Avram Traian. 2022 - 2022.
// File created on June 13 2022.

#include "Log.h"

#include "Platform.h"

namespace Blueberry {

	CharT Logger::m_Buffer[] = {};

	struct LoggerData
	{
		Logger::Verbosity AllowedVerbosity = Logger::Verbosity::None;
	};
	static LoggerData* s_LoggerData = nullptr;

	bool Logger::Initialize()
	{
		if (s_LoggerData)
			return false;
		
		s_LoggerData = bbnew LoggerData();
		if (!s_LoggerData)
			return false;

		s_LoggerData->AllowedVerbosity = Verbosity::Debug;

		return true;
	}

	void Logger::Shutdown()
	{
		if (!s_LoggerData)
			return;

		delete s_LoggerData;
		s_LoggerData = nullptr;
	}

	void Logger::SetVerbosity(Verbosity verbosity)
	{
		s_LoggerData->AllowedVerbosity = verbosity;
	}

	void Logger::Log(Verbosity verbosity, StringView message)
	{
		if ((uint8_t)verbosity < (uint8_t)s_LoggerData->AllowedVerbosity)
			return;

		if ((uint8_t)verbosity > (uint8_t)Verbosity::Fatal)
		{
			// TODO (Avr): Assert
			return;
		}

		static const uint32_t console_flags[] =
		{
			0,
			BLUE_CONSOLE_FLAG_BLACK_BACKGROUND | BLUE_CONSOLE_FLAG_PURPLE_TEXT,
			BLUE_CONSOLE_FLAG_BLACK_BACKGROUND | BLUE_CONSOLE_FLAG_GRAY_TEXT,
			BLUE_CONSOLE_FLAG_BLACK_BACKGROUND | BLUE_CONSOLE_FLAG_GREEN_TEXT,
			BLUE_CONSOLE_FLAG_BLACK_BACKGROUND | BLUE_CONSOLE_FLAG_BRIGHT_YELLOW_TEXT,
			BLUE_CONSOLE_FLAG_BLACK_BACKGROUND | BLUE_CONSOLE_FLAG_BRIGHT_RED_TEXT,
			BLUE_CONSOLE_FLAG_RED_BACKGROUND   | BLUE_CONSOLE_FLAG_BRIGHT_WHITE_TEXT
		};

		static const CharT* verbosity_names[] =
		{
			TEXT("[NONE] "),
			TEXT("[DEBUG]"),
			TEXT("[TRACE]"),
			TEXT("[INFO] "),
			TEXT("[WARN] "),
			TEXT("[ERROR]"),
			TEXT("[FATAL]")
		};

		SystemTime time;
		Platform::GetLocalSystemTime(time);

		static CharT buffer[8192] = {};
		auto written = std::format_to_n(
			buffer, BLUE_ARRAY_LENGTH(buffer),
			TEXT("[{:02}:{:02}:{:02}]{} BLUEBERRY: {}\n"),
			time.Hour, time.Minute, time.Second,
			verbosity_names[(uint8_t)verbosity],
			message.CStr());

		Platform::SetConsoleFlags(console_flags[(uint8_t)verbosity]);
		Platform::WriteToConsole({ buffer, (size_t)written.size });
	}

}