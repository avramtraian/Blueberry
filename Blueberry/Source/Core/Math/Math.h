// Copyright to Avram Traian. 2022 - 2022.
// File created on July 6 2022.

#pragma once

#include "Core/Base.h"

namespace Blueberry {

	/**
	* The namespace that stores the core templated math types & functions.
	*/
	namespace Math {

		/**
		* Used in checking equality of floating type variables.
		*/
		template<typename T> struct SmallValue {};

		template<> struct SmallValue<float>    { static constexpr float    V = 1e-4f; };
		template<> struct SmallValue<double>   { static constexpr double   V = 1e-8;  };
		template<> struct SmallValue<uint32_t> { static constexpr uint32_t V = 0u;    };
		template<> struct SmallValue<int32_t>  { static constexpr int32_t  V = 0;     };

		/**
		* Checks if two variables are equal. Usage in floating point types.
		* 
		* @param x The first variable to compare.
		* @param y The second variable to compare.
		* @param error_tolerance Maximum allowed (absolute) difference between the values.
		* 
		* @returns True if the are nearly equal (might not have the same binary representation); False otherwise.
		*/
		template<typename T>
		BLUE_FORCEINLINE bool constexpr IsNearlyEqual(T x, T y, T error_tolerance = SmallValue<T>::V)
		{
			T d = x - y;
			return -error_tolerance <= d && d <= error_tolerance;
		}

		/**
		* Clamps a value between two other values. Value is clamped in the interval [min, max].
		* 
		* @param value The value to be clamped.
		* @param min_val The minimum allowed value.
		* @param max_val The maximum allowed value.
		* 
		* @returns The clamped value. In the range [min_value, max_value].
		*/
		template<typename T>
		BLUE_FORCEINLINE T constexpr Clamp(T value, T min_val, T max_val)
		{
			return (value < min_val) ? min_val : ((value > max_val) ? max_val : value);
		}

		/**
		* Returns the smallest value between the two supplied variables.
		* 
		* @param x First value.
		* @param y Second value.
		* 
		* @returns The first value if x < y; y otherwise.
		*/
		template<typename T>
		BLUE_FORCEINLINE T constexpr Min(T x, T y)
		{
			return x < y ? x : y;
		}

		/**
		* Returns the biggest value between the two supplied variables.
		*
		* @param x First value.
		* @param y Second value.
		*
		* @returns The first value if x > y; y otherwise.
		*/
		template<typename T>
		BLUE_FORCEINLINE T constexpr Max(T x, T y)
		{
			return x > y ? x : y;
		}

		/**
		* Returns the absolute value (|x|).
		* 
		* @param x The value.
		* 
		* @returns The absolute value of x (x if x >= 0; -x otherwise).
		*/
		template<typename T>
		BLUE_FORCEINLINE T constexpr Absolute(T x)
		{
			return x < (T)0 ? -x : x;
		}

	}
	
	/**
	* The namespace that stores the core float values & functions.
	*/
	namespace Mathf {

		/**
		* PI constants.
		*/
		constexpr float PI                  = 3.1415926535897932f;
		constexpr float TWO_PI              = 2.0f * PI;
		constexpr float THREE_PI            = 3.0f * PI;
		constexpr float HALF_PI             = PI / 2.0f;
		constexpr float THIRD_PI            = PI / 3.0f;
		constexpr float QUARTER_PI          = PI / 4.0f;

		constexpr float ONE_OVER_PI         = 1.0f / PI;
		constexpr float ONE_OVER_TWO_PI     = 1.0f / TWO_PI;
		constexpr float ONE_OVER_THREE_PI   = 1.0f / THREE_PI;

		/**
		* Common square roots constants.
		*/
		constexpr float SQRT_TWO            = 1.4142135623730950f;
		constexpr float SQRT_THREE          = 1.7320508075688772f;
		constexpr float SQRT_FIVE           = 2.2360679774997896f;

		constexpr float ONE_OVER_SQRT_TWO   = 1.0f / SQRT_TWO;
		constexpr float ONE_OVER_SQRT_THREE = 1.0f / SQRT_THREE;
		constexpr float ONE_OVER_SQRT_FIVE  = 1.0f / SQRT_FIVE;

		/**
		* Radians & Degrees multipliers.
		*/
		constexpr float DEG_TO_RAD          = PI / 180.0f;
		constexpr float RAD_TO_DEG          = 180.0f / PI;

		/**
		* A number that is much larger than any valid number used in the engine.
		*/
		constexpr float BINFINITY           = 1e35f;

		//// Basic math functions.

		BLUEBERRY_API float SquareRoot(float x);

		BLUEBERRY_API float Power(float base, float exp);
		BLUEBERRY_API float Power(float base, int64_t exp);

		BLUEBERRY_API float Sin(float x);
		BLUEBERRY_API float Asin(float x);

		BLUEBERRY_API float Cos(float x);
		BLUEBERRY_API float Acos(float x);

		BLUEBERRY_API float Tan(float x);
		BLUEBERRY_API float Atan(float x);

		BLUE_FORCEINLINE constexpr float Degrees(float rad)
		{
			return rad * RAD_TO_DEG;
		}

		BLUE_FORCEINLINE constexpr float Radians(float deg)
		{
			return deg * DEG_TO_RAD;
		}

		// See Math::IsNearlyEqual.
		BLUE_FORCEINLINE constexpr bool IsNearlyEqual(float x, float y, float error_tolerance)
		{
			return Math::IsNearlyEqual<float>(x, y, error_tolerance);
		}

		// See Math::Clamp.
		BLUE_FORCEINLINE float constexpr Clamp(float value, float min_val, float max_val)
		{
			return Math::Clamp<float>(value, min_val, max_val);
		}

		// See Math::Min.
		BLUE_FORCEINLINE float constexpr Min(float x, float y)
		{
			return Math::Min<float>(x, y);
		}

		// See Math::Max.
		BLUE_FORCEINLINE float constexpr Max(float x, float y)
		{
			return Math::Max<float>(x, y);
		}

		// See Math::Absolute.
		BLUE_FORCEINLINE float constexpr Absolute(float x)
		{
			return Math::Absolute<float>(x);
		}

	}

	/**
	* The namespace that stores the core double values & functions.
	*/
	namespace Mathd {

		/**
		* PI constants.
		*/
		constexpr double PI                  = 3.1415926535897932;
		constexpr double TWO_PI              = 2.0 * PI;
		constexpr double THREE_PI            = 3.0 * PI;
		constexpr double HALF_PI             = PI / 2.0;
		constexpr double THIRD_PI            = PI / 3.0;
		constexpr double QUARTER_PI          = PI / 4.0;

		constexpr double ONE_OVER_PI         = 1.0 / PI;
		constexpr double ONE_OVER_TWO_PI     = 1.0 / TWO_PI;
		constexpr double ONE_OVER_THREE_PI   = 1.0 / THREE_PI;

		/**
		* Common square roots constants.
		*/
		constexpr double SQRT_TWO            = 1.4142135623730950;
		constexpr double SQRT_THREE          = 1.7320508075688772;
		constexpr double SQRT_FIVE           = 2.2360679774997896;

		constexpr double ONE_OVER_SQRT_TWO   = 1.0 / SQRT_TWO;
		constexpr double ONE_OVER_SQRT_THREE = 1.0 / SQRT_THREE;
		constexpr double ONE_OVER_SQRT_FIVE  = 1.0 / SQRT_FIVE;

		/**
		* Radians & Degrees multipliers.
		*/
		constexpr double DEG_TO_RAD          = PI / 180.0;
		constexpr double RAD_TO_DEG          = 180.0 / PI;

		/**
		* A number that is much larger than any valid number used in the engine.
		*/
		constexpr double BINFINITY           = 1e300;

		//// Basic math functions.

		BLUEBERRY_API double SquareRoot(double x);

		BLUEBERRY_API double Power(double base, double exp);
		BLUEBERRY_API double Power(double base, int64_t exp);

		BLUEBERRY_API double Sin(double x);
		BLUEBERRY_API double Asin(double x);

		BLUEBERRY_API double Cos(double x);
		BLUEBERRY_API double Acos(double x);

		BLUEBERRY_API double Tan(double x);
		BLUEBERRY_API double Atan(double x);

		BLUE_FORCEINLINE constexpr double Degrees(double rad)
		{
			return rad * RAD_TO_DEG;
		}

		BLUE_FORCEINLINE constexpr double Radians(double deg)
		{
			return deg * DEG_TO_RAD;
		}

		// See Math::IsNearlyEqual.
		BLUE_FORCEINLINE constexpr bool IsNearlyEqual(double x, double y, double error_tolerance)
		{
			return Math::IsNearlyEqual<double>(x, y, error_tolerance);
		}

		// See Math::Clamp.
		BLUE_FORCEINLINE double constexpr Clamp(double value, double min_val, double max_val)
		{
			return Math::Clamp<double>(value, min_val, max_val);
		}

		// See Math::Min.
		BLUE_FORCEINLINE double constexpr Min(double x, double y)
		{
			return Math::Min<double>(x, y);
		}

		// See Math::Max.
		BLUE_FORCEINLINE double constexpr Max(double x, double y)
		{
			return Math::Max<double>(x, y);
		}

		// See Math::Absolute.
		BLUE_FORCEINLINE double constexpr Absolute(double x)
		{
			return Math::Absolute<double>(x);
		}

	}

}