// Copyright to Avram Traian. 2022 - 2022.
// File created on July 8 2022.

#pragma once

#include "Math.h"
#include "Vector3.h"

namespace Blueberry {

	struct Matrix3
	{
	public:
		static constexpr Matrix3 Identity()
		{
			return Matrix3();
		}

	public:
		static Matrix3 Multiply(const Matrix3& m1, const Matrix3& m2)
		{
			Matrix3 out;

			const float* m1_data = m1.Data;
			const float* m2_data = m2.Data;
			float* out_data = out.Data;

			for (uint8_t i = 0; i < 3; i++)
			{
				for (uint8_t j = 0; j < 3; j++)
				{
					*out_data =
						m1_data[0] * m2_data[j + 0] +
						m1_data[1] * m2_data[j + 3] +
						m1_data[2] * m2_data[j + 6];
					out_data++;
				}
				m1_data += 3;
			}

			return out;
		}

		static Vector3 MultiplyVector(const Matrix3& m, const Vector3& v)
		{
			Vector3 out;

			out.X =
				m.Data[0] * v.X +
				m.Data[1] * v.Y +
				m.Data[2] * v.Z;

			out.Y =
				m.Data[3] * v.X +
				m.Data[4] * v.Y +
				m.Data[5] * v.Z;

			out.Z =
				m.Data[6] * v.X +
				m.Data[7] * v.Y +
				m.Data[8] * v.Z;

			return out;
		}

	public:
		constexpr Matrix3()
			: Data{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			}
		{}

		Matrix3(const Matrix3& other)
		{
			Memory::Copy(Data, other.Data, sizeof(Data));
		}

		constexpr Matrix3(
			float x00, float x01, float x02,
			float x10, float x11, float x12,
			float x20, float x21, float x22
		)
			: Data{
				x00, x01, x02,
				x10, x11, x12,
				x20, x21, x22
			}
		{}

	public:
		Matrix3& operator=(const Matrix3& other)
		{
			Memory::Copy(Data, other.Data, sizeof(Data));
			return *this;
		}

	public:
		float Data[9];
	};

}