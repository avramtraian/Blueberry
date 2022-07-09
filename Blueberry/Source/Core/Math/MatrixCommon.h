// Copyright to Avram Traian. 2022 - 2022.
// File created on July 9 2022.

#pragma once

#include "Matrix3.h"
#include "Matrix4.h"

namespace Blueberry {

	template<typename T>
	Matrix3t<T>::Matrix3t(const Matrix4t<T>& m4)
		: Data{
			m4.Data[0], m4.Data[1], m4.Data[2],
			m4.Data[4], m4.Data[5], m4.Data[6],
			m4.Data[8], m4.Data[9], m4.Data[10]
		}
	{}

	template<typename T>
	Matrix3t<T>& Matrix3t<T>::operator=(const Matrix4t<T>& m4)
	{
		Data[0] = m4.Data[0];
		Data[1] = m4.Data[1];
		Data[2] = m4.Data[2];

		Data[3] = m4.Data[4];
		Data[4] = m4.Data[5];
		Data[5] = m4.Data[6];

		Data[6] = m4.Data[8];
		Data[7] = m4.Data[9];
		Data[8] = m4.Data[10];

		return *this;
	}

	template<typename T>
	Matrix4t<T>::Matrix4t(const Matrix3t<T>& m3)
		: Data{
			m3.Data[0], m3.Data[1], m3.Data[2], (T)0,
			m3.Data[3], m3.Data[4], m3.Data[5], (T)0,
			m3.Data[6], m3.Data[7], m3.Data[8], (T)0,
			(T)0,       (T)0,      (T)0,        (T)1,
		}
	{}

	template<typename T>
	Matrix4t<T>& Matrix4t<T>::operator=(const Matrix3t<T>& m3)
	{
		Data[0]  = m3.Data[0];
		Data[1]  = m3.Data[1];
		Data[2]  = m3.Data[2];
		Data[3]  = (T)0;

		Data[4]  = m3.Data[3];
		Data[5]  = m3.Data[4];
		Data[6]  = m3.Data[5];
		Data[7]  = (T)0;

		Data[8]  = m3.Data[6];
		Data[9]  = m3.Data[7];
		Data[10] = m3.Data[8];
		Data[11] = (T)0;

		Data[12] = (T)0;
		Data[13] = (T)0;
		Data[14] = (T)0;
		Data[15] = (T)1;

		return *this;
	}

}