// Copyright to Avram Traian. 2022 - 2022.
// File created on June 14 2022.

#include "Memory.h"

#include "Core/Platform.h"
#include "Profiling/MemoryProfiler.h"

namespace Blueberry {

	struct MemoryData
	{
#if BLUE_DISABLE_MEMORY_PROFILING
		static constexpr bool EnableProfilingTools = false;
#else
		static inline    bool EnableProfilingTools = true;
#endif
	};
	static MemoryData* s_MemoryData = nullptr;

	bool Memory::Initialize(bool enable_profiling_tools)
	{
		if (s_MemoryData)
			return false;

#if !BLUE_DISABLE_MEMORY_PROFILING
		MemoryData::EnableProfilingTools = enable_profiling_tools;
#endif

		s_MemoryData = (MemoryData*)Platform::Allocate(sizeof(MemoryData));
		if (!s_MemoryData)
			return false;
		new (s_MemoryData) MemoryData();

		if (MemoryData::EnableProfilingTools)
		{
			if (!MemoryProfiler::Initialize())
				return false;
		}

		return true;
	}

	void Memory::Shutdown()
	{
		if (!s_MemoryData)
			return;

		if (MemoryData::EnableProfilingTools)
		{
			MemoryProfiler::Shutdown();
		}

		s_MemoryData->~MemoryData();
		Platform::Free(s_MemoryData);
		s_MemoryData = nullptr;
	}

	void Memory::EnableMemoryProfiling()
	{
#if !BLUE_DISABLE_MEMORY_PROFILING
		if (!MemoryData::EnableProfilingTools)
		{
			MemoryData::EnableProfilingTools = true;
			MemoryProfiler::Initialize();
		}
#endif
	}

	void Memory::DisableMemoryProfiling()
	{
#if !BLUE_DISABLE_MEMORY_PROFILING
		if (MemoryData::EnableProfilingTools)
		{
			MemoryData::EnableProfilingTools = false;
			MemoryProfiler::Shutdown();
		}
#endif
	}

	void Memory::Copy(void* destination, const void* source, SizeT copy_size)
	{
		memcpy(destination, source, (size_t)copy_size);
	}

	void Memory::Set(void* destination, ByteT value, SizeT set_size)
	{
		memset(destination, value, (size_t)set_size);
	}

	void Memory::Zero(void* destination, SizeT zero_size)
	{
		memset(destination, 0, (size_t)zero_size);
	}

	void* Memory::AllocateRaw(SizeT block_size)
	{
		if (block_size == 0)
			return nullptr;

		return Platform::Allocate(block_size);
	}

	void* Memory::Allocate(SizeT block_size)
	{
		void* memory_block = AllocateRaw(block_size);

		if (s_MemoryData->EnableProfilingTools)
		{
			MemoryProfiler::TrackAllocation(memory_block, block_size, TEXT("Unknown"), TEXT("Unknown"), 0);
		}

		return memory_block;
	}

	void* Memory::AllocateTaggedI(SizeT block_size, const CharT* file, const CharT* function_sig, uint32_t line)
	{
		void* memory_block = AllocateRaw(block_size);

		if (s_MemoryData->EnableProfilingTools)
		{
			MemoryProfiler::TrackAllocation(memory_block, block_size, file, function_sig, line);
		}

		return memory_block;
	}

	void Memory::FreeRaw(void* memory_block)
	{
		if (memory_block == nullptr)
			return;

		Platform::Free(memory_block);
	}

	void Memory::Free(void* memory_block)
	{
		if (s_MemoryData->EnableProfilingTools)
		{
			MemoryProfiler::TrackDeallocation(memory_block);
		}

		FreeRaw(memory_block);
	}

}

void* operator new(size_t block_size)
{
	return Blueberry::Memory::Allocate(block_size);
}

void* operator new(size_t block_size, const Blueberry::CharT* file, const Blueberry::CharT* function_sig, uint32_t line)
{
	return Blueberry::Memory::AllocateTaggedI(block_size, file, function_sig, line);
}

void operator delete(void* memory_block) noexcept
{
	Blueberry::Memory::Free(memory_block);
}