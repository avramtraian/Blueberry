#pragma once

#include "Base.h"
#include "Platform.h"

#if BLUE_BUILD_DEBUG
	#define BLUE_ENABLE_DASSERTS (1)
	#define BLUE_ENABLE_ASSERTS  (1)
	#define BLUE_ENABLE_VERIFIES (1)

#elif BLUE_BUILD_RELEASE
	#define BLUE_ENABLE_DASSERTS (0)
	#define BLUE_ENABLE_ASSERTS  (1)
	#define BLUE_ENABLE_VERIFIES (1)

#elif BLUE_BUILD_SHIPPING
	#define BLUE_ENABLE_DASSERTS (0)
	#define BLUE_ENABLE_ASSERTS  (0)
	#define BLUE_ENABLE_VERIFIES (0)
#endif

#if BLUE_ENABLE_DASSERTS
	#define BLUE_CORE_DASSERT(Expression) if (!(Expression)) { ::Blueberry::Platform::OpenErrorDialog(); BLUE_DEBUGBREAK(); }

#else
	#define BLUE_CORE_DASSERT(Expression)
#endif

#if BLUE_ENABLE_ASSERTS
	#define BLUE_CORE_ASSERT(Expression) if (!(Expression)) { ::Blueberry::Platform::OpenErrorDialog(); BLUE_DEBUGBREAK(); }

#else
	#define BLUE_CORE_ASSERT(Expression)
#endif

#if BLUE_ENABLE_VERIFIES
	#define BLUE_CORE_VERIFY(Expression) if (!(Expression)) { ::Blueberry::Platform::OpenErrorDialog(); BLUE_DEBUGBREAK(); }

#else
	#define BLUE_CORE_VERIFY(Expression) Expression
#endif