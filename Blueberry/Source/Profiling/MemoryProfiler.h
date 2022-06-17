#pragma once

#include "Core/Base.h"
#include "Core/Containers/HashTable.h"

#if BLUE_BUILD_SHIPPING
	#define BLUE_DISABLE_MEMORY_PROFILING (1)
#else
	#define BLUE_DISABLE_MEMORY_PROFILING (0)
#endif

namespace Blueberry {

	struct LineMemoryProfilingInfo
	{
		SizeT    TotalAllocated          = 0;
		SizeT    TotalDeallocated        = 0;
		SizeT    TotalAllocationsCount   = 0;
		SizeT    TotalDeallocationsCount = 0;
	};

	struct FileMemoryProfilingInfo
	{
		SizeT        TotalAllocated          = 0;
		SizeT        TotalDeallocated        = 0;
		SizeT        TotalAllocationsCount   = 0;
		SizeT        TotalDeallocationsCount = 0;

		HashTable<uint32_t, LineMemoryProfilingInfo, UntrackedAllocator> LinesProfilingInfo;
	};

	class BLUEBERRY_API MemoryProfiler
	{
	public:
		static bool Initialize();

		static void Shutdown();

	public:
		static void TrackAllocation(void* memory_block, SizeT block_size, const TCHAR* file, const TCHAR* function_sig, uint32_t line);
		static void TrackDeallocation(void* memory_block);

		static const HashTable<const TCHAR*, FileMemoryProfilingInfo, UntrackedAllocator>& Data();
	};

}