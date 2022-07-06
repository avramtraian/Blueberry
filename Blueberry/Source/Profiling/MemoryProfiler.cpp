// Copyright to Avram Traian. 2022 - 2022.
// File created on June 17 2022.

#include "MemoryProfiler.h"

#include "Core/Platform.h"

namespace Blueberry {

	struct AllocationInfo
	{
		const CharT* File      = TEXT("Unknown");
		uint32_t     Line      = 0;
		SizeT        BlockSize = 0;
	};

	struct MemoryProfilerData
	{
#if BLUE_ENABLE_MEMORY_PROFILING
		static inline bool IsEnabled = false;
#endif

		HashTable<void*,        AllocationInfo,          UntrackedAllocator> Allocations;
		HashTable<const CharT*, FileMemoryProfilingInfo, UntrackedAllocator> FilesProfilingInfo;
	};
	static MemoryProfilerData* s_MemoryProfilerData = nullptr;

	bool MemoryProfiler::Initialize()
	{
		if (s_MemoryProfilerData)
			return false;

		s_MemoryProfilerData = (MemoryProfilerData*)Platform::Allocate(sizeof(MemoryProfilerData));
		if (!s_MemoryProfilerData)
			return false;
		new (s_MemoryProfilerData) MemoryProfilerData();

		return true;
	}

	void MemoryProfiler::Shutdown()
	{
		if (!s_MemoryProfilerData)
			return;

		Disable();
		s_MemoryProfilerData->~MemoryProfilerData();
		Platform::Free(s_MemoryProfilerData);

		s_MemoryProfilerData = nullptr;
	}

	bool MemoryProfiler::IsEnabled()
	{
#if BLUE_ENABLE_MEMORY_PROFILING
		return MemoryProfilerData::IsEnabled;
#else
		return false;
#endif
	}

	void MemoryProfiler::Enable()
	{
#if BLUE_ENABLE_MEMORY_PROFILING
		MemoryProfilerData::IsEnabled = true;
#endif
	}

	void MemoryProfiler::Disable()
	{
#if BLUE_ENABLE_MEMORY_PROFILING
		MemoryProfilerData::IsEnabled = false;
#endif
	}

	void MemoryProfiler::TrackAllocation(void* memory_block, SizeT block_size, const CharT* file, const CharT* function_sig, uint32_t line)
	{
		BLUE_CORE_ASSERT(IsEnabled());

		if (memory_block == nullptr)
			return;

		AllocationInfo allocation_info;
		allocation_info.File = file;
		allocation_info.Line = line;
		allocation_info.BlockSize = block_size;
		s_MemoryProfilerData->Allocations.Add(memory_block, allocation_info);

		auto& file_profiling = s_MemoryProfilerData->FilesProfilingInfo[file];
		file_profiling.TotalAllocated += block_size;
		file_profiling.TotalAllocationsCount++;

		auto& line_profiling = file_profiling.LinesProfilingInfo[line];
		line_profiling.TotalAllocated += block_size;
		line_profiling.TotalAllocationsCount++;
	}

	void MemoryProfiler::TrackDeallocation(void* memory_block)
	{
		BLUE_CORE_ASSERT(IsEnabled());

		if (memory_block == nullptr)
			return;

		SizeT allocation_info_index = s_MemoryProfilerData->Allocations.Find(memory_block);

		// The allocation might have been done when the memory profiler wasn't enabled.
		if (allocation_info_index == BLUE_INVALID_SIZE)
			return;

		auto& allocation_info = s_MemoryProfilerData->Allocations.Entries()[allocation_info_index].B;

		auto& file_profiling = s_MemoryProfilerData->FilesProfilingInfo[allocation_info.File];
		file_profiling.TotalDeallocated += allocation_info.BlockSize;
		file_profiling.TotalDeallocationsCount++;

		auto& line_profiling = file_profiling.LinesProfilingInfo[allocation_info.Line];
		line_profiling.TotalDeallocated += allocation_info.BlockSize;
		line_profiling.TotalDeallocationsCount++;

		s_MemoryProfilerData->Allocations.RemoveIndex(allocation_info_index);
	}

	const HashTable<const CharT*, FileMemoryProfilingInfo, UntrackedAllocator>& MemoryProfiler::Data()
	{
		return s_MemoryProfilerData->FilesProfilingInfo;
	}

}