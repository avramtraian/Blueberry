// Copyright to Avram Traian. 2022 - 2022.
// File created on July 7 2022.

#pragma once

#include "Math.h"

namespace Blueberry {

	struct Vector3
	{
	public:
		static float LengthSquared(const Vector3& v)
		{
			return (v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z);
		}

		static float Length(const Vector3& v)
		{
			return Math::SquareRoot(Vector3::LengthSquared(v));
		}

		static float DistanceSquared(const Vector3& v1, const Vector3& v2)
		{
			float x = v1.X - v2.X;
			float y = v1.Y - v2.Y;
			float z = v1.Z - v2.Z;
			return (x * x) + (y * y) + (z * z);
		}

		static float Distance(const Vector3& v1, const Vector3& v2)
		{
			return Math::SquareRoot(Vector3::DistanceSquared(v1, v2));
		}

		static Vector3 Normalize(const Vector3& v)
		{
			float one_over_length = 1.0f / Length(v);
			return Vector3(
				v.X * one_over_length,
				v.Y * one_over_length,
				v.Z * one_over_length
			);
		}

		static float Dot(const Vector3& v1, const Vector3& v2)
		{
			return (v1.X * v2.X) + (v1.Y * v2.Y) + (v1.Z * v2.Z);
		}

		static Vector3 Cross(const Vector3& v1, const Vector3& v2)
		{
			return Vector3(
				v1.Y * v2.Z - v1.Z * v2.Y,
				v1.X * v2.Z - v1.Z * v2.X,
				v1.X * v2.Y - v1.Y * v2.X
			);
		}

	public:
		Vector3()
			: X(0.0f), Y(0.0f), Z(0.0f)
		{}

		Vector3(const Vector3& other)
			: X(other.X), Y(other.Y), Z(other.Z)
		{}

		Vector3(float x, float y, float z)
			: X(x), Y(y) , Z(z)
		{}
		
		Vector3(float scalar)
			: X(scalar), Y(scalar), Z(scalar)
		{}

	public:
		Vector3& operator=(const Vector3& other)
		{
			X = other.X;
			Y = other.Y;
			Z = other.Z;
			return *this;
		}

		bool operator==(const Vector3& other) const
		{
			return
				Math::IsNearlyEqual(X, other.X, Math::KINDA_SMALL_NUMBER) &&
				Math::IsNearlyEqual(Y, other.Y, Math::KINDA_SMALL_NUMBER) &&
				Math::IsNearlyEqual(Z, other.Z, Math::KINDA_SMALL_NUMBER);
		}

		bool operator!=(const Vector3& other) const
		{
			return !(*this == other);
		}

	public:
		float X, Y, Z;
	};

}