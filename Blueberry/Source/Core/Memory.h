#pragma once

#include "Core/Base.h"

namespace Blueberry {

	class BLUEBERRY_API Memory
	{
	public:
		static bool Initialize(bool enable_profiling_tools);

		static void Shutdown();

		static void EnableMemoryProfiling();

		static void DisableMemoryProfiling();

	public:
		static void Copy(void* destination, const void* source, SizeT copy_size);
		static void Set(void* destination, int value, SizeT set_size);
		static void Zero(void* destination, SizeT zero_size);

	public:
		BLUE_NODISCARD static void* AllocateRaw(SizeT block_size);
		BLUE_NODISCARD static void* Allocate(SizeT block_size);
		BLUE_NODISCARD static void* AllocateTaggedI(SizeT block_size, const TCHAR* file, const TCHAR* function_sig, uint32_t line);

		static void FreeRaw(void* memory_block);
		static void Free(void* memory_block);
	};

	class BLUEBERRY_API HeapAllocator
	{
	public:
		constexpr static uint64_t GetStaticAllocatorID() { return 1; }
	
	public:
		static void* Allocate(SizeT block_size)
		{
			return Memory::Allocate(block_size);
		}

		static void* AllocateTaggedI(SizeT block_size, const TCHAR* file, const TCHAR* function_sig, uint32_t line)
		{
			return Memory::AllocateTaggedI(block_size, file, function_sig, line);
		}

		static void Free(void* memory_block, SizeT)
		{
			return Memory::Free(memory_block);
		}

	public:
		constexpr bool operator==(const HeapAllocator&) const
		{
			return true;
		}
	};

	class BLUEBERRY_API UntrackedAllocator
	{
	public:
		constexpr static uint64_t GetStaticAllocatorID() { return 2; }

	public:
		static void* Allocate(SizeT block_size)
		{
			return Memory::AllocateRaw(block_size);
		}

		static void* AllocateTaggedI(SizeT block_size, const TCHAR* file, const TCHAR* function_sig, uint32_t line)
		{
			return Memory::AllocateRaw(block_size);
		}

		static void Free(void* memory_block, SizeT)
		{
			return Memory::FreeRaw(memory_block);
		}

	public:
		constexpr bool operator==(const UntrackedAllocator&) const
		{
			return true;
		}
	};

	template<typename AllocatorTypeA, typename AllocatorTypeB>
	bool CompareAllocators(const AllocatorTypeA& allocator_a, const AllocatorTypeB& allocator_b)
	{
		if (AllocatorTypeA::GetStaticAllocatorID() != AllocatorTypeB::GetStaticAllocatorID())
			return false;

		return (allocator_a == allocator_b);
	}

}

void* operator new(size_t block_size);
void* operator new(size_t block_size, const Blueberry::TCHAR* file, const Blueberry::TCHAR* function_sig, uint32_t line);
inline void* operator new(size_t, void*) noexcept;

void operator delete(void* memory_block) noexcept;

#define AllocateTagged(block_size) AllocateTaggedI(block_size, BLUE_FILE, BLUE_FUNCTION_SIG, BLUE_LINE)

#define bbnew new (BLUE_FILE, BLUE_FUNCTION_SIG, BLUE_LINE)