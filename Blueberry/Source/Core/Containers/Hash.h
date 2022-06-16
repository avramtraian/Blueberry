#pragma once

#include "Core/Base.h"

namespace Blueberry {

	using HashT = uint64_t;

	template<typename T>
	class Hasher
	{
	public:
		static HashT Get(const T&)
		{
			return 0;
		}
	};

	template<>
	class Hasher<uint8_t>
	{
	public:
		static HashT Get(const uint8_t& value)
		{
			return (HashT)value;
		}
	};

	template<>
	class Hasher<uint16_t>
	{
	public:
		static HashT Get(const uint16_t& value)
		{
			return (HashT)value;
		}
	};

	template<>
	class Hasher<uint32_t>
	{
	public:
		static HashT Get(const uint32_t& value)
		{
			return (HashT)value;
		}
	};

	template<>
	class Hasher<uint64_t>
	{
	public:
		static HashT Get(const uint64_t& value)
		{
			return (HashT)value;
		}
	};

	template<>
	class Hasher<int8_t>
	{
	public:
		static HashT Get(const int8_t& value)
		{
			return (HashT)(*(const uint8_t*)&value);
		}
	};

	template<>
	class Hasher<int16_t>
	{
	public:
		static HashT Get(const int16_t& value)
		{
			return (HashT)(*(const uint16_t*)&value);
		}
	};

	template<>
	class Hasher<int32_t>
	{
	public:
		static HashT Get(const int32_t& value)
		{
			return (HashT)(*(const uint32_t*)&value);
		}
	};

	template<>
	class Hasher<int64_t>
	{
	public:
		static HashT Get(const int64_t& value)
		{
			return (HashT)(*(const uint64_t*)&value);
		}
	};

	template<>
	class Hasher<float>
	{
	public:
		static HashT Get(const float& value)
		{
			return (HashT)(*(const uint32_t*)&value);
		}
	};

	template<>
	class Hasher<double>
	{
	public:
		static HashT Get(const double& value)
		{
			return (HashT)(*(const uint64_t*)&value);
		}
	};

	template<>
	class Hasher<TCHAR>
	{
	public:
		static HashT Get(const TCHAR& value)
		{
			return (HashT)value;
		}
	};

	template<>
	class Hasher<const TCHAR*>
	{
	public:
		static HashT Get(const TCHAR* const& value)
		{
			return 1;
		}
	};

	template<>
	class Hasher<void*>
	{
	public:
		static HashT Get(void* const& value)
		{
			return (SizeT)value;
		}
	};

}