// Copyright to Avram Traian. 2022 - 2022.
// File created on July 6 2022.

#pragma once

#include "Core/Base.h"

namespace Blueberry { namespace Math {

	constexpr float PI                  = 3.1415926535897932f;
	constexpr float TWO_PI              = 2.0f * PI;
	constexpr float THREE_PI            = 3.0f * PI;
	constexpr float HALF_PI             = PI / 2.0f;
	constexpr float THIRD_PI            = PI / 3.0f;
	constexpr float QUARTER_PI          = PI / 4.0f;

	constexpr float ONE_OVER_PI         = 1.0f / PI;
	constexpr float ONE_OVER_TWO_PI     = 1.0f / TWO_PI;
	constexpr float ONE_OVER_THREE_PI   = 1.0f / THREE_PI;

	constexpr float SQRT_TWO            = 1.4142135623730950f;
	constexpr float SQRT_THREE          = 1.7320508075688772f;
	constexpr float SQRT_FIVE           = 2.2360679774997896f;

	constexpr float ONE_OVER_SQRT_TWO   = 1.0f / SQRT_TWO;
	constexpr float ONE_OVER_SQRT_THREE = 1.0f / SQRT_THREE;
	constexpr float ONE_OVER_SQRT_FIVE  = 1.0f / SQRT_FIVE;

	constexpr float DEG_TO_RAD          = PI / 180.0f;
	constexpr float RAD_TO_DEG          = 180.0f / PI;

	constexpr float FINFINITY           = 1e35f;

	constexpr float KINDA_SMALL_NUMBER  = 1e-4f;
	constexpr float SMALL_NUMBER        = 1e-6f;

	template<typename T>
	BLUE_FORCEINLINE T constexpr Clamp(T value, T min_val, T max_val)
	{
		return (value < min_val) ? min_val : ((value > max_val) ? max_val : value);
	}

	template<typename T>
	BLUE_FORCEINLINE T constexpr Min(T x, T y)
	{
		return x < y ? x : y;
	}

	template<typename T>
	BLUE_FORCEINLINE T constexpr Max(T x, T y)
	{
		return x > y ? x : y;
	}

	template<typename T>
	BLUE_FORCEINLINE T constexpr Absolute(T x)
	{
		return x < (T)0 ? -x : x;
	}

	BLUEBERRY_API float SquareRoot(float x);
	BLUEBERRY_API double SquareRootD(double x);

	BLUEBERRY_API float Power(float base, float exp);
	BLUEBERRY_API float Power(float base, int64_t exp);

	BLUEBERRY_API double PowerD(double base, double exp);
	BLUEBERRY_API double PowerD(double base, int64_t exp);

	BLUEBERRY_API int64_t PowerI(int64_t base, uint64_t exp);

	BLUEBERRY_API float Sin(float x);
	BLUEBERRY_API double SinD(double x);
	BLUEBERRY_API float Asin(float x);
	BLUEBERRY_API double AsinD(double x);

	BLUEBERRY_API float Cos(float x);
	BLUEBERRY_API double CosD(double x);
	BLUEBERRY_API float Acos(float x);
	BLUEBERRY_API double AcosD(double x);

	BLUEBERRY_API float Tan(float x);
	BLUEBERRY_API double TanD(double x);
	BLUEBERRY_API float Atan(float x);
	BLUEBERRY_API double AtanD(double x);

	BLUE_FORCEINLINE constexpr float Deg(float rad)
	{
		return rad * RAD_TO_DEG;
	}

	BLUE_FORCEINLINE constexpr double DegD(double rad)
	{
		return rad * RAD_TO_DEG;
	}

	BLUE_FORCEINLINE constexpr float Rad(float deg)
	{
		return deg * DEG_TO_RAD;
	}

	BLUE_FORCEINLINE constexpr double RadD(double deg)
	{
		return deg * DEG_TO_RAD;
	}

	BLUE_FORCEINLINE constexpr bool IsNearlyEqual(float x, float y, float error_tolerance)
	{
		return (Absolute(x - y) <= error_tolerance);
	}

	BLUE_FORCEINLINE constexpr bool IsNearlyEqualD(double x, double y, double error_tolerance)
	{
		return (Absolute(x - y) <= error_tolerance);
	}

} }