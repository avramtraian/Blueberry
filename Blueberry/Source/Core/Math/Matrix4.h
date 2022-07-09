// Copyright to Avram Traian. 2022 - 2022.
// File created on July 7 2022.

#pragma once

#include "Math.h"
#include "Vector4.h"

namespace Blueberry {

	struct Matrix4
	{
	public:
		static constexpr Matrix4 Identity()
		{
			return Matrix4();
		}

	public:
		static Matrix4 Multiply(const Matrix4& m1, const Matrix4& m2)
		{
			Matrix4 out;
			
			const float* m1_data = m1.Data;
			const float* m2_data = m2.Data;
			float* out_data = out.Data;

			for (uint8_t i = 0; i < 4; i++)
			{
				for (uint8_t j = 0; j < 4; j++)
				{
					*out_data =
						m1_data[0] * m2_data[j + 0] +
						m1_data[1] * m2_data[j + 4] +
						m1_data[2] * m2_data[j + 8] +
						m1_data[3] * m2_data[j + 12];
					out_data++;
				}
				m1_data += 4;
			}

			return out;
		}

		static Vector4 MultiplyVector(const Matrix4& m, const Vector4& v)
		{
			Vector4 out;

			out.X =
				m.Data[0]  * v.X +
				m.Data[1]  * v.Y +
				m.Data[2]  * v.Z +
				m.Data[3]  * v.W;

			out.Y =
				m.Data[4]  * v.X +
				m.Data[5]  * v.Y +
				m.Data[6]  * v.Z +
				m.Data[7]  * v.W;

			out.Z =
				m.Data[8]  * v.X +
				m.Data[9]  * v.Y +
				m.Data[10] * v.Z +
				m.Data[11] * v.W;

			out.W =
				m.Data[12] * v.X +
				m.Data[13] * v.Y +
				m.Data[14] * v.Z +
				m.Data[15] * v.W;

			return out;
		}

		static Matrix4 Transpose(const Matrix4& m)
		{
			Matrix4 out;
			for (uint8_t i = 0; i < 4; i++)
			{
				for (uint8_t j = 0; j < 4; j++)
				{
					out.Data[4 * i + j] = m.Data[4 * j + i];
				}
			}
			return out;
		}

		static float Determinant(const Matrix4& m)
		{
			float determinant = 0.0f;
			return determinant;
		}

		static Matrix4 Inverse(const Matrix4& m)
		{
			Matrix4 out;
			return out;
		}

	public:
		static Matrix4 Translate(const Vector3& v)
		{
			Matrix4 out;
			out.Data[3]  = v.X;
			out.Data[7]  = v.Y;
			out.Data[11] = v.Z;
			return out;
		}

		static Matrix4 RotateEulerX(float angle)
		{
			Matrix4 out;

			float s = Math::Sin(angle);
			float c = Math::Cos(angle);

			out.Data[5]  = c;
			out.Data[6]  = -s;
			out.Data[9]  = s;
			out.Data[10] = c;

			return out;
		}

		static Matrix4 RotateEulerY(float angle)
		{
			Matrix4 out;

			float s = Math::Sin(angle);
			float c = Math::Cos(angle);

			out.Data[0]  = c;
			out.Data[2]  = s;
			out.Data[8]  = -s;
			out.Data[10] = c;

			return out;
		}

		static Matrix4 RotateEulerZ(float angle)
		{
			Matrix4 out;
			
			float s = Math::Sin(angle);
			float c = Math::Cos(angle);

			out.Data[0] = c;
			out.Data[1] = -s;
			out.Data[4] = s;
			out.Data[5] = c;

			return out;
		}

		static Matrix4 RotateEulerXYZ(const Vector3& angles)
		{
			Matrix4 rx = Matrix4::RotateEulerX(angles.X);
			Matrix4 ry = Matrix4::RotateEulerY(angles.Y);
			Matrix4 rz = Matrix4::RotateEulerZ(angles.Z);

			return rx * ry * rz;
		}

		static Matrix4 Scale(const Vector3& v)
		{
			Matrix4 out;
			out.Data[0]  = v.X;
			out.Data[5]  = v.Y;
			out.Data[10] = v.Z;
			return out;
		}

		static Matrix4 Perspective(float fov, float aspect_ratio, float near_clip, float far_clip)
		{
			Matrix4 out;

			float half_tan = Math::Tan(fov * 0.5f);
			float one_over_nmf = 1.0f / (near_clip - far_clip);

			out.Data[0] = 1.0f / (aspect_ratio * half_tan);
			out.Data[5] = 1.0f / half_tan;
			out.Data[10] = (near_clip + far_clip) * one_over_nmf;
			out.Data[11] = -1.0f;
			out.Data[14] = 2.0f * near_clip * far_clip * one_over_nmf;

			return out;
		}

		static Matrix4 Ortographic(float left, float right, float bottom, float top, float near_clip, float far_clip)
		{
			Matrix4 out;

			float lr = 1.0f / (left - right);
			float bt = 1.0f / (bottom - top);
			float nf = 1.0f / (near_clip - far_clip);

			out.Data[0] = -2.0f * lr;
			out.Data[5] = -2.0f * bt;
			out.Data[10] = -2.0f * nf;

			out.Data[12] = (left + right) * lr;
			out.Data[13] = (bottom + top) / bt;
			out.Data[14] = (near_clip + far_clip) * nf;

			return out;
		}

	public:
		constexpr Matrix4()
			: Data{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			}
		{}

		Matrix4(
			float x00, float x01, float x02, float x03,
			float x10, float x11, float x12, float x13,
			float x20, float x21, float x22, float x23,
			float x30, float x31, float x32, float x33
		)
			: Data{
				x00, x01, x02, x03,
				x10, x11, x12, x13,
				x20, x21, x22, x23,
				x30, x31, x32, x33
			}
		{}

		constexpr Matrix4(const Matrix4& other)
			: Data{
				other.Data[0],  other.Data[1],  other.Data[2],  other.Data[3],
				other.Data[4],  other.Data[5],  other.Data[6],  other.Data[7],
				other.Data[8],  other.Data[9],  other.Data[10], other.Data[11],
				other.Data[12], other.Data[13], other.Data[14], other.Data[15]
			}
		{}

	public:
		Matrix4& operator=(const Matrix4& other)
		{
			Memory::Copy(Data, other.Data, sizeof(Data));
			return *this;
		}

		float* operator[](uint8_t index)
		{
			return Data + (index * 4);
		}

		const float* operator[](uint8_t index) const
		{
			return Data + (index * 4);
		}

		Matrix4 operator*(const Matrix4& other) const
		{
			return Matrix4::Multiply(*this, other);
		}

		Vector4 operator*(const Vector4& v) const
		{
			return Matrix4::MultiplyVector(*this, v);
		}

		bool operator==(const Matrix4& other) const
		{
			for (uint8_t index = 0; index < 16; index++)
			{
				if (!Math::IsNearlyEqual(Data[index], other.Data[index], Math::KINDA_SMALL_NUMBER))
					return false;
			}
			return true;
		}

		bool operator!=(const Matrix4& other) const
		{
			return !(*this == other);
		}

	public:
		float Data[16];
	};

}