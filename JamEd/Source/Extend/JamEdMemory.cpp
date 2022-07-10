// Copyright to Avram Traian. 2022 - 2022.
// File created on June 17 2022.

#include "Core/Memory.h"

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