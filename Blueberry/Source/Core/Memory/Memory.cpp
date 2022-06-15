#include "Memory.h"

#include "Core/Platform/Platform.h"

namespace Blueberry {

	struct MemoryData
	{

	};
	static MemoryData* s_MemoryData = nullptr;

	bool Memory::Initialize()
	{
		if (s_MemoryData)
			return false;

		s_MemoryData = (MemoryData*)Platform::Allocate(sizeof(MemoryData));
		if (!s_MemoryData)
			return false;
		new (s_MemoryData) MemoryData();

		return true;
	}

	void Memory::Shutdown()
	{
		if (!s_MemoryData)
			return;

		s_MemoryData->~MemoryData();
		Platform::Free(s_MemoryData);
		s_MemoryData = nullptr;
	}

	void Memory::Copy(void* destination, const void* source, SizeT copy_size)
	{
		memcpy(destination, source, (size_t)copy_size);
	}

	void Memory::Set(void* destination, int value, SizeT set_size)
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
		if (block_size == 0)
			return nullptr;

		return AllocateRaw(block_size);
	}

	void Memory::FreeRaw(void* memory_block)
	{
		if (memory_block == nullptr)
			return;

		Platform::Free(memory_block);
	}

	void Memory::Free(void* memory_block)
	{
		if (memory_block == nullptr)
			return;

		FreeRaw(memory_block);
	}

}

void* operator new(size_t block_size)
{
	return Blueberry::Memory::Allocate(block_size);
}

void operator delete(void* memory_block) noexcept
{
	Blueberry::Memory::Free(memory_block);
}