#pragma once

#include "Core/Base.h"

namespace Blueberry {

	class BLUEBERRY_API Memory
	{
	public:
		static bool Initialize();

		static void Shutdown();

	public:
		void Copy(void* destination, const void* source, SizeT copy_size);
		void Set(void* destination, int value, SizeT set_size);
		void Zero(void* destination, SizeT zero_size);

	public:
		static void* AllocateRaw(SizeT block_size);
		static void* Allocate(SizeT block_size);

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
inline void* operator new(size_t, void*) noexcept;

void operator delete(void* memory_block) noexcept;