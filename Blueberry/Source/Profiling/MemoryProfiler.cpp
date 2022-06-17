#include "MemoryProfiler.h"

#include "Core/Platform.h"

namespace Blueberry {

	struct AllocationInfo
	{
		const TCHAR* File      = TEXT("Unknown");
		uint32_t     Line      = 0;
		SizeT        BlockSize = 0;
	};

	struct MemoryProfilerData
	{
		HashTable<void*,        AllocationInfo,          UntrackedAllocator> Allocations;
		HashTable<const TCHAR*, FileMemoryProfilingInfo, UntrackedAllocator> FilesProfilingInfo;
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

		s_MemoryProfilerData->~MemoryProfilerData();
		Platform::Free(s_MemoryProfilerData);

		s_MemoryProfilerData = nullptr;
	}

	void MemoryProfiler::TrackAllocation(void* memory_block, SizeT block_size, const TCHAR* file, const TCHAR* function_sig, uint32_t line)
	{
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
		if (memory_block == nullptr)
			return;

		SizeT allocation_info_index = s_MemoryProfilerData->Allocations.Find(memory_block);
		auto& allocation_info = s_MemoryProfilerData->Allocations.Entries()[allocation_info_index].B;

		auto& file_profiling = s_MemoryProfilerData->FilesProfilingInfo[allocation_info.File];
		file_profiling.TotalDeallocated += allocation_info.BlockSize;
		file_profiling.TotalDeallocationsCount++;

		auto& line_profiling = file_profiling.LinesProfilingInfo[allocation_info.Line];
		line_profiling.TotalDeallocated += allocation_info.BlockSize;
		line_profiling.TotalDeallocationsCount++;

		s_MemoryProfilerData->Allocations.RemoveIndex(allocation_info_index);
	}

	const HashTable<const TCHAR*, FileMemoryProfilingInfo, UntrackedAllocator>& MemoryProfiler::Data()
	{
		return s_MemoryProfilerData->FilesProfilingInfo;
	}

}