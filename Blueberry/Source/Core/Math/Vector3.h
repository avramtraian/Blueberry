// Copyright to Avram Traian. 2022 - 2022.
// File created on July 7 2022.

#pragma once

#include "Math.h"

namespace Blueberry {

	template<typename T>
	struct Vector2t;
	template<typename T>
	struct Vector4t;

	template<typename T>
	struct Vector3t
	{
	public:
		static T LengthSquared(const Vector3t& v)
		{
			return (v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z);
		}

		static T Length(const Vector3t& v)
		{
			return Math::SquareRoot(Vector3t::LengthSquared(v));
		}

		static T DistanceSquared(const Vector3t& v1, const Vector3t& v2)
		{
			T x = v1.X - v2.X;
			T y = v1.Y - v2.Y;
			T z = v1.Z - v2.Z;
			return (x * x) + (y * y) + (z * z);
		}

		static T Distance(const Vector3t& v1, const Vector3t& v2)
		{
			return Math::SquareRoot(Vector3t::DistanceSquared(v1, v2));
		}

		static Vector3t Normalize(const Vector3t& v)
		{
			T one_over_length = (T)1 / Vector3t::Length(v);
			return Vector3t(
				v.X * one_over_length,
				v.Y * one_over_length,
				v.Z * one_over_length
			);
		}

		static T Dot(const Vector3t& v1, const Vector3t& v2)
		{
			return (v1.X * v2.X) + (v1.Y * v2.Y) + (v1.Z * v2.Z);
		}

		static Vector3t Cross(const Vector3t& v1, const Vector3t& v2)
		{
			return Vector3t(
				v1.Y * v2.Z - v1.Z * v2.Y,
				v1.X * v2.Z - v1.Z * v2.X,
				v1.X * v2.Y - v1.Y * v2.X
			);
		}

	public:
		Vector3t()
			: X((T)0), Y((T)0), Z((T)0)
		{}

		Vector3t(const Vector3t& other)
			: X(other.X), Y(other.Y), Z(other.Z)
		{}

		Vector3t(T x, T y, T z)
			: X(x), Y(y) , Z(z)
		{}
		
		Vector3t(T scalar)
			: X(scalar), Y(scalar), Z(scalar)
		{}

		// Definition is in 'VectorCommon.h'.
		Vector3t(const Vector2t<T>& v2);

		// Definition is in 'VectorCommon.h'.
		Vector3t(const Vector4t<T>& v4);

	public:
		Vector3t& operator=(const Vector3t& other)
		{
			X = other.X;
			Y = other.Y;
			Z = other.Z;
			return *this;
		}

		// Definition is in 'VectorCommon.h'.
		Vector3t& operator=(const Vector2t<T>& v2);

		// Definition is in 'VectorCommon.h'.
		Vector3t& operator=(const Vector4t<T>& v4);

		T& operator[](uint8_t index)
		{
			return *(&X + index);
		}

		const T& operator[](uint8_t index) const
		{
			return *(&X + index);
		}

		bool operator==(const Vector3t& other) const
		{
			return
				Math::IsNearlyEqual<T>(X, other.X, Math::KINDA_SMALL_NUMBER) &&
				Math::IsNearlyEqual<T>(Y, other.Y, Math::KINDA_SMALL_NUMBER) &&
				Math::IsNearlyEqual<T>(Z, other.Z, Math::KINDA_SMALL_NUMBER);
		}

		bool operator!=(const Vector3t& other) const
		{
			return !(*this == other);
		}

	public:
		T X, Y, Z;
	};

	using Vector3  = Vector3t<float>;
	using Vector3f = Vector3t<float>;
	using Vector3d = Vector3t<double>;
	using Vector3i = Vector3t<int32_t>;
	using Vector3u = Vector3t<uint32_t>;

}