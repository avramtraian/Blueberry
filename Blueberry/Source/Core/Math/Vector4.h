// Copyright to Avram Traian. 2022 - 2022.
// File created on July 8 2022.

#pragma once

#include "Math.h"

namespace Blueberry {

	template<typename T, typename Q>
	struct Vector2t;
	template<typename T, typename Q>
	struct Vector3t;

	template<typename T, typename Q>
	struct Vector4t
	{
	public:
		Vector4t()
			: X((T)0), Y((T)0), Z((T)0), W((T)0)
		{}

		Vector4t(const Vector4t& other)
			: X(other.X), Y(other.Y), Z(other.Z), W(other.W)
		{}

		Vector4t(T x, T y, T z, T w)
			: X(x), Y(y), Z(z), W(w)
		{}

		Vector4t(T scalar)
			: X(scalar), Y(scalar), Z(scalar), W(scalar)
		{}

		// Definition is in 'VectorCommon.h'.
		Vector4t(const Vector2t<T, Q>& v2);

		// Definition is in 'VectorCommon.h'.
		Vector4t(const Vector3t<T, Q>& v3);

	public:
		Vector4t& operator=(const Vector4t& other)
		{
			X = other.X;
			Y = other.Y;
			Z = other.Z;
			W = other.W;
			return *this;
		}

		// Definition is in 'VectorCommon.h'.
		Vector4t& operator=(const Vector2t<T, Q>& v2);

		// Definition is in 'VectorCommon.h'.
		Vector4t& operator=(const Vector3t<T, Q>& v3);

		T& operator[](uint8_t index)
		{
			return *(&X + index);
		}

		const T& operator[](uint8_t index) const
		{
			return *(&X + index);
		}

		bool operator==(const Vector4t& other) const
		{
			return
				Math::IsNearlyEqual<T>(X, other.X) &&
				Math::IsNearlyEqual<T>(Y, other.Y) &&
				Math::IsNearlyEqual<T>(Z, other.Z) &&
				Math::IsNearlyEqual<T>(W, other.W);
		}

		bool operator!=(const Vector4t& other) const
		{
			return !(*this == other);
		}

	public:
		T X, Y, Z, W;
	};

	using Vector4  = Vector4t<float,    float>;
	using Vector4f = Vector4t<float,    float>;
	using Vector4d = Vector4t<double,   double>;
	using Vector4i = Vector4t<int32_t,  float>;
	using Vector4u = Vector4t<uint32_t, float>;

}