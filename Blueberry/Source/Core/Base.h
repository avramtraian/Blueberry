#pragma once

#ifndef BLUE_PLATFORM_WINDOWS
	#error Blueberry only supports Windows!
	#define BLUE_PLATFORM_WINDOWS (0)
#endif

#if BLUE_PLATFORM_WINDOWS
	#ifndef BLUE_PLATFORM_WIN64
		#error Blueberry only supports 64-bit architecture!
	#endif

	#if defined(BLUE_BUILD_SHARED_LIBRARY)
		#define BLUEBERRY_API     __declspec(dllexport)
	#elif defined(BLUE_USE_SHARED_LIBRARY)
		#define BLUEBERRY_API     __declspec(dllimport)
	#else
		#error An API specifier must be provided!
		#define BLUEBERRY_API
	#endif
#endif

#ifndef _UNICODE
	#error Blueberry requires Unicode!
#endif

#define __BLUE_TEXT(T)            L##T
#define TEXT(T)                   __BLUE_TEXT(T)

#ifdef _MSC_BUILD
	#define BLUE_COMPILER_MSVC    (1)
#endif

#ifndef BLUE_COMPILER_MSVC
	#error Blueberry can only be compiled with MSVC!
	#define BLUE_COMPILER_MSVC    (0)
#endif

#if BLUE_COMPILER_MSVC
	#define BLUE_FORCEINLINE      __forceinline
	#define BLUE_DEBUGBREAK()     __debugbreak()

	#define BLUE_FUNCTION         TEXT(__FUNCTION__)
	#define BLUE_FUNCTION_SIG     TEXT(__FUNCSIG__)

	// class 'A' needs to have dll-interface to be used by clients of class 'B'
	#pragma warning (disable : 4251)

#endif

#define BLUE_FILE                 TEXT(__FILE__)
#define BLUE_LINE                 __LINE__
#define BLUE_DATE                 TEXT(__DATE__)

#define BLUE_NODISCARD            [[nodiscard]]
#define BLUE_MAYBE_UNUSED         [[maybe_unused]]
#define BLUE_LIKELY               [[likely]]
#define BLUE_UNLIKELY             [[unlikely]]

#ifndef BLUE_BUILD_DEBUG
	#define BLUE_BUILD_DEBUG      (0)
#endif

#ifndef BLUE_BUILD_RELEASE
	#define BLUE_BUILD_RELEASE    (0)
#endif

#ifndef BLUE_BUILD_SHIPPING
	#define BLUE_BUILD_SHIPPING   (0)
#endif

#include <cstdint>

#define BLUE_ARRAY_LENGTH(Arr)    (sizeof(Arr) / sizeof(Arr[0]))

namespace Blueberry {

	using SizeT    = uint64_t;

	using PtrT     = uint64_t;

	using CharT    = wchar_t;

	using ByteT    = uint8_t;

	using NullptrT = decltype(nullptr);

	constexpr uint8_t  BLUE_MIN_UINT8    = 0x00;
	constexpr uint16_t BLUE_MIN_UINT16   = 0x00;
	constexpr uint32_t BLUE_MIN_UINT32   = 0x00;
	constexpr uint64_t BLUE_MIN_UINT64   = 0x00;
	
	constexpr uint8_t  BLUE_MAX_UINT8    = 0xFF;
	constexpr uint16_t BLUE_MAX_UINT16   = 0xFFFF;
	constexpr uint32_t BLUE_MAX_UINT32   = 0xFFFFFFFF;
	constexpr uint64_t BLUE_MAX_UINT64   = 0xFFFFFFFFFFFFFFFF;

	constexpr int8_t   BLUE_MIN_INT8     = -0x7F - 1;
	constexpr int16_t  BLUE_MIN_INT16    = -0x7FFF - 1;
	constexpr int32_t  BLUE_MIN_INT32    = -0x7FFFFFFF - 1;
	constexpr int64_t  BLUE_MIN_INT64    = -0x7FFFFFFFFFFFFFFF - 1;
	
	constexpr int8_t   BLUE_MAX_INT8     = 0x7F;
	constexpr int16_t  BLUE_MAX_INT16    = 0x7FFF;
	constexpr int32_t  BLUE_MAX_INT32    = 0x7FFFFFFF;
	constexpr int64_t  BLUE_MAX_INT64    = 0x7FFFFFFFFFFFFFFF;
	
	constexpr SizeT    BLUE_MIN_SIZE     = BLUE_MIN_UINT64;
	constexpr SizeT    BLUE_MAX_SIZE     = BLUE_MAX_UINT64;
	constexpr SizeT    BLUE_INVALID_SIZE = BLUE_MAX_SIZE;
	
	constexpr ByteT    BLUE_MIN_BYTE     = BLUE_MIN_UINT8;
	constexpr ByteT    BLUE_MAX_BYTE     = BLUE_MAX_UINT8;

}

namespace Blueberry {

	template<typename T>
	struct RemoveReference
	{
		using Type = T;
	};

	template<typename T>
	struct RemoveReference<T&>
	{
		using Type = T;
	};

	template<typename T>
	struct RemoveReference<T&&>
	{
		using Type = T;
	};

	template<typename T>
	using RemoveReferenceType = typename RemoveReference<T>::Type;

	template<typename T>
	struct RemoveConst
	{
		using Type = T;
	};

	template<typename T>
	struct RemoveConst<const T>
	{
		using Type = T;
	};

	template<typename T>
	using RemoveConstType = typename RemoveConst<T>::Type;

	template<typename T>
	constexpr RemoveReferenceType<T>&& Move(T&& object) noexcept
	{
		return static_cast<RemoveReferenceType<T>&&>(object);
	}

	template<typename T>
	constexpr T&& Forward(RemoveReferenceType<T>& object) noexcept
	{
		return static_cast<T&&>(object);
	}

}