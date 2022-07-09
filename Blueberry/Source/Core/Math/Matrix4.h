// Copyright to Avram Traian. 2022 - 2022.
// File created on July 7 2022.

#pragma once

#include "Math.h"
#include "Vector4.h"

namespace Blueberry {

	template<typename T>
	struct Matrix3t;

	template<typename T>
	struct Matrix4t
	{
	public:
		static constexpr Matrix4t Identity()
		{
			return Matrix4t();
		}

	public:
		static Matrix4t Multiply(const Matrix4t& m1, const Matrix4t& m2)
		{
			Matrix4t out;
			
			const T* m1_data = m1.Data;
			const T* m2_data = m2.Data;
			T* out_data = out.Data;

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

		static Vector4 MultiplyVector(const Matrix4t& m, const Vector4& v)
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

		static Matrix4t Transpose(const Matrix4t& m)
		{
			Matrix4t out;
			for (uint8_t i = 0; i < 4; i++)
			{
				for (uint8_t j = 0; j < 4; j++)
				{
					out.Data[4 * i + j] = m.Data[4 * j + i];
				}
			}
			return out;
		}

		static T Determinant(const Matrix4t& m)
		{
			T determinant = (T)0;
			return determinant;
		}

		static Matrix4t Inverse(const Matrix4t& m)
		{
			Matrix4t out;
			return out;
		}

	public:
		static Matrix4t Translate(const Vector3& v)
		{
			Matrix4t out;
			out.Data[3]  = v.X;
			out.Data[7]  = v.Y;
			out.Data[11] = v.Z;
			return out;
		}

		static Matrix4t RotateEulerX(T angle)
		{
			Matrix4t out;

			T s = Math::Sin(angle);
			T c = Math::Cos(angle);

			out.Data[5]  = c;
			out.Data[6]  = -s;
			out.Data[9]  = s;
			out.Data[10] = c;

			return out;
		}

		static Matrix4t RotateEulerY(T angle)
		{
			Matrix4t out;

			T s = Math::Sin(angle);
			T c = Math::Cos(angle);

			out.Data[0]  = c;
			out.Data[2]  = s;
			out.Data[8]  = -s;
			out.Data[10] = c;

			return out;
		}

		static Matrix4t RotateEulerZ(T angle)
		{
			Matrix4t out;
			
			T s = Math::Sin(angle);
			T c = Math::Cos(angle);

			out.Data[0] = c;
			out.Data[1] = -s;
			out.Data[4] = s;
			out.Data[5] = c;

			return out;
		}

		static Matrix4t RotateEulerXYZ(const Vector3& angles)
		{
			Matrix4t rx = Matrix4t::RotateEulerX(angles.X);
			Matrix4t ry = Matrix4t::RotateEulerY(angles.Y);
			Matrix4t rz = Matrix4t::RotateEulerZ(angles.Z);

			return rx * ry * rz;
		}

		static Matrix4t Scale(const Vector3& v)
		{
			Matrix4t out;
			out.Data[0]  = v.X;
			out.Data[5]  = v.Y;
			out.Data[10] = v.Z;
			return out;
		}

		static Matrix4t Perspective(T fov, T aspect_ratio, T near_clip, T far_clip)
		{
			Matrix4t out;

			T half_tan = Math::Tan(fov * (T)0.5);
			T one_over_nmf = (T)1 / (near_clip - far_clip);

			out.Data[0] = (T)1 / (aspect_ratio * half_tan);
			out.Data[5] = (T)1 / half_tan;
			out.Data[10] = (near_clip + far_clip) * one_over_nmf;
			out.Data[11] = -(T)1;
			out.Data[14] = (T)2 * near_clip * far_clip * one_over_nmf;

			return out;
		}

		static Matrix4t Ortographic(T left, T right, T bottom, T top, T near_clip, T far_clip)
		{
			Matrix4t out;

			T lr = (T)1 / (left - right);
			T bt = (T)1 / (bottom - top);
			T nf = (T)1 / (near_clip - far_clip);

			out.Data[0] = (T)(-2.0) * lr;
			out.Data[5] = (T)(-2.0) * bt;
			out.Data[10] = (T)(-2.0) * nf;

			out.Data[12] = (left + right) * lr;
			out.Data[13] = (bottom + top) / bt;
			out.Data[14] = (near_clip + far_clip) * nf;

			return out;
		}

	public:
		constexpr Matrix4t()
			: Data{
				(T)1, (T)0, (T)0, (T)0,
				(T)0, (T)1, (T)0, (T)0,
				(T)0, (T)0, (T)1, (T)0,
				(T)0, (T)0, (T)0, (T)1
			}
		{}

		Matrix4t(
			T x00, T x01, T x02, T x03,
			T x10, T x11, T x12, T x13,
			T x20, T x21, T x22, T x23,
			T x30, T x31, T x32, T x33
		)
			: Data{
				x00, x01, x02, x03,
				x10, x11, x12, x13,
				x20, x21, x22, x23,
				x30, x31, x32, x33
			}
		{}

		constexpr Matrix4t(const Matrix4t& other)
			: Data{
				other.Data[0],  other.Data[1],  other.Data[2],  other.Data[3],
				other.Data[4],  other.Data[5],  other.Data[6],  other.Data[7],
				other.Data[8],  other.Data[9],  other.Data[10], other.Data[11],
				other.Data[12], other.Data[13], other.Data[14], other.Data[15]
			}
		{}

		// Definition is in 'MatrixCommon.h'.
		Matrix4t(const Matrix3t<T>& m3);

	public:
		Matrix4t& operator=(const Matrix4t& other)
		{
			Memory::Copy(Data, other.Data, sizeof(Data));
			return *this;
		}

		// Definition is in 'MatrixCommon.h'.
		Matrix4t& operator=(const Matrix3t<T>& m3);

		T* operator[](uint8_t index)
		{
			return Data + (index * 4);
		}

		const T* operator[](uint8_t index) const
		{
			return Data + (index * 4);
		}

		Matrix4t operator*(const Matrix4t& other) const
		{
			return Matrix4t::Multiply(*this, other);
		}

		Vector4 operator*(const Vector4& v) const
		{
			return Matrix4t::MultiplyVector(*this, v);
		}

		bool operator==(const Matrix4t& other) const
		{
			for (uint8_t index = 0; index < 16; index++)
			{
				if (!Math::IsNearlyEqual<T>(Data[index], other.Data[index], Math::KINDA_SMALL_NUMBER))
					return false;
			}
			return true;
		}

		bool operator!=(const Matrix4t& other) const
		{
			return !(*this == other);
		}

	public:
		T Data[16];
	};

	using Matrix4  = Matrix4t<float>;
	using Matrix4f = Matrix4t<float>;
	using Matrix4d = Matrix4t<double>;
	using Matrix4i = Matrix4t<int32_t>;
	using Matrix4u = Matrix4t<uint32_t>;

}