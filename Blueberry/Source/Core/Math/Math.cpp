// Copyright to Avram Traian. 2022 - 2022.
// File created on July 6 2022.

#include "Math.h"

#include <cmath>
#include <cstdlib>

namespace Blueberry { namespace Math {

	float SquareRoot(float x)
	{
		return sqrtf(x);
	}

	double SquareRootD(double x)
	{
		return sqrt(x);
	}

	float Power(float base, float exp)
	{
		return powf(base, exp);
	}

	float Power(float base, int64_t exp)
	{
		float result = 1.0f;

		for (int64_t index = 0; index < exp; index++)
			result *= base;

		if (exp < 0)
		{
			float one_over_base = 1.0f / base;
			for (int64_t index = exp; index > 0; index--)
				result *= one_over_base;
		}

		return result;
	}

	double PowerD(double base, double exp)
	{
		return pow(base, exp);
	}

	double PowerD(double base, int64_t exp)
	{
		double result = 1.0;

		for (int64_t index = 0; index < exp; index++)
			result *= base;

		if (exp < 0)
		{
			double one_over_base = 1.0 / base;
			for (int64_t index = exp; index > 0; index--)
				result *= one_over_base;
		}

		return result;
	}

	int64_t PowerI(int64_t base, uint64_t exp)
	{
		int64_t result = 1;

		for (int64_t index = 0; index < exp; index++)
			result *= base;

		return result;
	}

	float Sin(float x)
	{
		return sinf(x);
	}

	double SinD(double x)
	{
		return sin(x);
	}

	float Asin(float x)
	{
		return asinf(x);
	}

	double AsinD(double x)
	{
		return asin(x);
	}

	float Cos(float x)
	{
		return cosf(x);
	}

	double CosD(double x)
	{
		return cos(x);
	}

	float Acos(float x)
	{
		return acosf(x);
	}

	double AcosD(double x)
	{
		return acos(x);
	}

	float Tan(float x)
	{
		return tanf(x);
	}

	double TanD(double x)
	{
		return tan(x);
	}

	float Atan(float x)
	{
		return atanf(x);
	}

	double AtanD(double x)
	{
		return atan(x);
	}

} }