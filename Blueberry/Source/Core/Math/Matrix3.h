// Copyright to Avram Traian. 2022 - 2022.
// File created on July 8 2022.

#pragma once

#include "Math.h"
#include "Vector3.h"

namespace Blueberry {

	template<typename T>
	struct Matrix4t;

	template<typename T>
	struct Matrix3t
	{
	public:
		static constexpr Matrix3t Identity()
		{
			return Matrix3t();
		}

	public:
		static Matrix3t Multiply(const Matrix3t& m1, const Matrix3t& m2)
		{
			Matrix3t out;

			const T* m1_data = m1.Data;
			const T* m2_data = m2.Data;
			T* out_data = out.Data;

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

		static Vector3 MultiplyVector(const Matrix3t& m, const Vector3& v)
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
		constexpr Matrix3t()
			: Data{
				(T)1, (T)0, (T)0,
				(T)0, (T)1, (T)0,
				(T)0, (T)0, (T)1
			}
		{}

		Matrix3t(const Matrix3t& other)
		{
			Memory::Copy(Data, other.Data, sizeof(Data));
		}

		constexpr Matrix3t(
			T x00, T x01, T x02,
			T x10, T x11, T x12,
			T x20, T x21, T x22
		)
			: Data{
				x00, x01, x02,
				x10, x11, x12,
				x20, x21, x22
			}
		{}

		// Definition is in 'MatrixCommon.h'.
		Matrix3t(const Matrix4t<T>& m4);

	public:
		Matrix3t& operator=(const Matrix3t& other)
		{
			Memory::Copy(Data, other.Data, sizeof(Data));
			return *this;
		}

		// Definition is in 'MatrixCommon.h'.
		Matrix3t& operator=(const Matrix4t<T>& m4);

	public:
		T Data[9];
	};

	using Matrix3  = Matrix3t<float>;
	using Matrix3f = Matrix3t<float>;
	using Matrix3d = Matrix3t<double>;
	using Matrix3i = Matrix3t<int32_t>;
	using Matrix3u = Matrix3t<uint32_t>;

}