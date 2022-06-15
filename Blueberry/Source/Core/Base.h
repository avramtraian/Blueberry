#pragma once

#ifndef BLUE_PLATFORM_WINDOWS
	#error Blueberry only supports Windows!
	#define BLUE_PLATFORM_WINDOWS (0)
#endif

#if BLUE_PLATFORM_WINDOWS
	#ifndef BLUE_PLATFORM_WIN64
		#error Blueberry only supports 64-bit!
	#endif

	#ifdef BLUE_BUILD_DLL
		#define BLUEBERRY_API __declspec(dllexport)
	#else
		#define BLUEBERRY_API __declspec(dllimport)
	#endif
#endif

#ifdef _MSC_BUILD
	#define BLUE_COMPILER_MSVC (1)
#endif

#ifndef BLUE_COMPILER_MSVC
	#error Blueberry can only be compiled with MSVC!
	#define BLUE_COMPILER_MSVC (0)
#endif

#if BLUE_COMPILER_MSVC
	#define BLUE_FORCEINLINE   __forceinline
	#define BLUE_DEBUGBREAK()  __debugbreak()

	#define BLUE_FUNCTION      __FUNCTION__
	#define BLUE_FUNCTION_SIG  __FUNCSIG__

	// class 'A' needs to have dll - interface to be used by clients of class 'B'
	#pragma warning (disable : 4251)

#endif

#define BLUE_FILE              __FILE__
#define BLUE_LINE              __LINE__
#define BLUE_DATE              __DATE__

#define BLUE_NODISCARD         [[nodiscard]]
#define BLUE_MAYBE_UNUSED      [[maybe_unused]]
#define BLUE_LIKELY            [[likely]]
#define BLUE_UNLIKELY          [[unlikely]]

#ifndef BLUE_BUILD_DEBUG
	#define BLUE_BUILD_DEBUG (0)
#endif

#ifndef BLUE_BUILD_RELEASE
	#define BLUE_BUILD_RELEASE (0)
#endif

#ifndef BLUE_BUILD_SHIPPING
	#define BLUE_BUILD_SHIPPING (0)
#endif

#include <cstdint>

#ifndef _UNICODE
	#error Blueberry requires Unicode!
#endif

#define BLUE_TEXT(x) L##x
#define TEXT(x) BLUE_TEXT(x)

#define BLUE_ARRAY_LENGTH(Arr) (sizeof(Arr) / sizeof(Arr[0]))

namespace Blueberry {

	using TCHAR = wchar_t;

	using SizeT = uint64_t;

	constexpr SizeT BLUE_INVALID_SIZE = 0xffffffffffffffff;

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