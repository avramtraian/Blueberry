// Copyright to Avram Traian. 2022 - 2022.
// File created on June 16 2022.

#pragma once

#include "Core/Base.h"

#define BLUE_DECL_HASH_PRIMITIVE(T, Bits)                   \
	template<>                                              \
	struct Hasher<T>                                        \
	{                                                       \
	public:                                                 \
		static HashT Get(T const& value)                    \
		{                                                   \
			return (HashT)(*(const uint##Bits##_t*)&value); \
		}                                                   \
	}

namespace Blueberry {

	using HashT = uint64_t;

	template<typename T>
	struct Hasher
	{
	public:
		/*
		static HashT Get(const T&)
		{
			return HASH_OF_THE_OBJECT;
		}
		*/
	};

	BLUE_DECL_HASH_PRIMITIVE(uint8_t,     8 );
	BLUE_DECL_HASH_PRIMITIVE(uint16_t,    16);
	BLUE_DECL_HASH_PRIMITIVE(uint32_t,    32);
	BLUE_DECL_HASH_PRIMITIVE(uint64_t,    64);

	BLUE_DECL_HASH_PRIMITIVE(int8_t,      8 );
	BLUE_DECL_HASH_PRIMITIVE(int16_t,     16);
	BLUE_DECL_HASH_PRIMITIVE(int32_t,     32);
	BLUE_DECL_HASH_PRIMITIVE(int64_t,     64);

	BLUE_DECL_HASH_PRIMITIVE(float,       32);
	BLUE_DECL_HASH_PRIMITIVE(double,      64);

	BLUE_DECL_HASH_PRIMITIVE(const void*, 64);
	BLUE_DECL_HASH_PRIMITIVE(void*,       64);

	BLUE_DECL_HASH_PRIMITIVE(CharT,       16);

	template<>
	struct Hasher<const CharT*>
	{
	public:
		static HashT Get(const CharT* const& value)
		{
			return std::hash<const wchar_t*>()(value);
		}
	};

	template<>
	struct Hasher<CharT*>
	{
	public:
		static HashT Get(CharT* const& value)
		{
			return Hasher<const CharT*>::Get((const CharT*)value);
		}
	};

}