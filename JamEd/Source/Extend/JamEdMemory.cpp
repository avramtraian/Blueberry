#include "Core/Memory.h"

void* operator new(size_t block_size)
{
	return Blueberry::Memory::Allocate(block_size);
}

void* operator new(size_t block_size, const Blueberry::TCHAR* file, const Blueberry::TCHAR* function_sig, uint32_t line)
{
	return Blueberry::Memory::AllocateTaggedI(block_size, file, function_sig, line);
}

void operator delete(void* memory_block) noexcept
{
	Blueberry::Memory::Free(memory_block);
}