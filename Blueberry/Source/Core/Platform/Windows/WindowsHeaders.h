#pragma once

#include "Core/Base.h"

#if BLUE_PLATFORM_WINDOWS
	#ifdef TEXT
		#undef TEXT
	#endif

	#include <Windows.h>
	#include <Windowsx.h>
#else
	#error Trying to compile a Windows-only file. Check your files.
#endif