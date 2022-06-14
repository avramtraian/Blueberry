#pragma once

#include "Core/Base.h"
#include "Core/Containers/String.h"

namespace Blueberry {
	
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

	class BLUEBERRY_API Platform
	{
	public:
		static bool Initialize();

		static void Shutdown();

	public:
		static void* MemoryAllocate(SizeT block_size);

		static void MemoryFree(void* memory_block);

	public:
		static void TimeGetLocalTime(SystemTime& out_local_time);

	public:
		static void ConsoleSetFlags(uint32_t flags);
		
		static uint32_t ConsoleGetFlags();

		static void ConsoleWrite(StringView message);
	};

	enum ConsoleFlagsEnum : uint32_t
	{
		BLUE_CONSOLE_FLAG_NONE = 0,

		BLUE_CONSOLE_FLAG_BLACK_TEXT               = 0x00,
		BLUE_CONSOLE_FLAG_BLUE_TEXT                = 0x01,
		BLUE_CONSOLE_FLAG_GREEN_TEXT               = 0x02,
		BLUE_CONSOLE_FLAG_AQUA_TEXT                = 0x03,
		BLUE_CONSOLE_FLAG_RED_TEXT                 = 0x04,
		BLUE_CONSOLE_FLAG_PURPLE_TEXT              = 0x05,
		BLUE_CONSOLE_FLAG_YELLOW_TEXT              = 0x06,
		BLUE_CONSOLE_FLAG_WHITE_TEXT               = 0x07,
		BLUE_CONSOLE_FLAG_GRAY_TEXT                = 0x08,
		BLUE_CONSOLE_FLAG_BRIGHT_BLUE_TEXT         = 0x09,
		BLUE_CONSOLE_FLAG_BRIGHT_GREEN_TEXT        = 0x0A,
		BLUE_CONSOLE_FLAG_BRIGHT_AQUA_TEXT         = 0x0B,
		BLUE_CONSOLE_FLAG_BRIGHT_RED_TEXT          = 0x0C,
		BLUE_CONSOLE_FLAG_BRIGHT_PURPLE_TEXT       = 0x0D,
		BLUE_CONSOLE_FLAG_BRIGHT_YELLOW_TEXT       = 0x0E,
		BLUE_CONSOLE_FLAG_BRIGHT_WHITE_TEXT        = 0x0F,

		BLUE_CONSOLE_FLAG_BLACK_BACKGROUND         = 0x00 << 4,
		BLUE_CONSOLE_FLAG_BLUE_BACKGROUND          = 0x01 << 4,
		BLUE_CONSOLE_FLAG_GREEN_BACKGROUND         = 0x02 << 4,
		BLUE_CONSOLE_FLAG_AQUA_BACKGROUND          = 0x03 << 4,
		BLUE_CONSOLE_FLAG_RED_BACKGROUND           = 0x04 << 4,
		BLUE_CONSOLE_FLAG_PURPLE_BACKGROUND        = 0x05 << 4,
		BLUE_CONSOLE_FLAG_YELLOW_BACKGROUND        = 0x06 << 4,
		BLUE_CONSOLE_FLAG_WHITE_BACKGROUND         = 0x07 << 4,
		BLUE_CONSOLE_FLAG_GRAY_BACKGROUND          = 0x08 << 4,
		BLUE_CONSOLE_FLAG_BRIGHT_BLUE_BACKGROUND   = 0x09 << 4,
		BLUE_CONSOLE_FLAG_BRIGHT_GREEN_BACKGROUND  = 0x0A << 4,
		BLUE_CONSOLE_FLAG_BRIGHT_AQUA_BACKGROUND   = 0x0B << 4,
		BLUE_CONSOLE_FLAG_BRIGHT_RED_BACKGROUND    = 0x0C << 4,
		BLUE_CONSOLE_FLAG_BRIGHT_PURPLE_BACKGROUND = 0x0D << 4,
		BLUE_CONSOLE_FLAG_BRIGHT_YELLOW_BACKGROUND = 0x0E << 4,
		BLUE_CONSOLE_FLAG_BRIGHT_WHITE_BACKGROUND  = 0x0F << 4,
	};

}