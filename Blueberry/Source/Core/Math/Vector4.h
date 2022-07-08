// Copyright to Avram Traian. 2022 - 2022.
// File created on July 8 2022.

#pragma once

#include "Math.h"

namespace Blueberry {

	struct Vector4
	{
	public:


	public:
		Vector4()
			: X(0.0f), Y(0.0f), Z(0.0f), W(0.0f)
		{}

		Vector4(const Vector4& other)
			: X(other.X), Y(other.Y), Z(other.Z), W(other.W)
		{}

		Vector4(float x, float y, float z, float w)
			: X(x), Y(y), Z(z), W(w)
		{}

		Vector4(float scalar)
			: X(scalar), Y(scalar), Z(scalar), W(scalar)
		{}

	public:
		Vector4& operator=(const Vector4& other)
		{
			X = other.X;
			Y = other.Y;
			Z = other.Z;
			W = other.W;
			return *this;
		}

		float& operator[](uint8_t index)
		{
			return *(&X + index);
		}

		const float& operator[](uint8_t index) const
		{
			return *(&X + index);
		}

	public:
		float X, Y, Z, W;
	};

}