// Copyright to Avram Traian. 2022 - 2022.
// File created on July 9 2022.

#pragma once

#include "Math.h"

namespace Blueberry {

	template<typename T>
	struct Vector3t;
	template<typename T>
	struct Vector4t;

	template<typename T>
	struct Vector2t
	{
	public:
		static T LengthSquared(const Vector2t& v)
		{
			return (v.X * v.X) + (v.Y * v.Y);
		}

		static T Length(const Vector2t& v)
		{
			return Math::SquareRoot(Vector2t::LengthSquared(v));
		}

		static T DistanceSquared(const Vector2t& v1, const Vector2t& v2)
		{
			T x = v1.X - v2.X;
			T y = v1.Y - v2.Y;
			return (x * x) + (y * y);
		}
		
		static T Distance(const Vector2t& v1, const Vector2t& v2)
		{
			return Math::SquareRoot(Vector2t::DistanceSquared(v1, v2));
		}

		static Vector2t Normalize(const Vector2t& v)
		{
			T one_over_length = (T)1 / Vector2t::Length(v);
			return Vector2t(v.X * one_over_length, v.Y * one_over_length);
		}

		static T Dot(const Vector2t& v1, const Vector2t& v2)
		{
			return (v1.X * v2.X) + (v1.Y * v2.Y);
		}

	public:
		Vector2t()
			: X((T)0), Y((T)0)
		{}

		Vector2t(const Vector2t& other)
			: X(other.X), Y(other.Y)
		{}

		Vector2t(T x, T y)
			: X(x), Y(y)
		{}

		Vector2t(T scalar)
			: X(scalar), Y(scalar)
		{}

		// Definition is in 'VectorCommon.h'.
		Vector2t(const Vector3t<T>& v3);

		// Definition is in 'VectorCommon.h'.
		Vector2t(const Vector4t<T>& v4);

	public:
		Vector2t& operator=(const Vector2t& other)
		{
			X = other.X;
			Y = other.Y;
			return *this;
		}

		// Definition is in 'VectorCommon.h'.
		Vector2t& operator=(const Vector3t<T>& v3);

		// Definition is in 'VectorCommon.h'.
		Vector2t& operator=(const Vector4t<T>& v4);

		T& operator[](uint8_t index)
		{
			return *(&X + index);
		}

		const T& operator[](uint8_t index) const
		{
			return *(&X + index);
		}

		bool operator==(const Vector2t& other) const
		{
			return
				Math::IsNearlyEqual<T>(X, other.X, Math::KINDA_SMALL_NUMBER) &&
				Math::IsNearlyEqual<T>(Y, other.Y, Math::KINDA_SMALL_NUMBER);
		}

		bool operator!=(const Vector2t& other) const
		{
			return !(*this == other);
		}

	public:
		T X, Y;
	};

	using Vector2  = Vector2t<float>;
	using Vector2f = Vector2t<float>;
	using Vector2d = Vector2t<double>;
	using Vector2i = Vector2t<int32_t>;
	using Vector2u = Vector2t<uint32_t>;

}