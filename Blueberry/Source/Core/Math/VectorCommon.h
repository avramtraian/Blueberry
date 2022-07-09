// Copyright to Avram Traian. 2022 - 2022.
// File created on July 9 2022.

#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Blueberry {

	////////////////////////////////////////////
	// Begin Vector2 ///////////////////////////
	////////////////////////////////////////////

	template<typename T>
	Vector2t<T>::Vector2t(const Vector3t<T>& v3)
		: X(v3.X), Y(v3.Y)
	{}

	template<typename T>
	Vector2t<T>::Vector2t(const Vector4t<T>& v4)
		: X(v4.X), Y(v4.Y)
	{}

	template<typename T>
	Vector2t<T>& Vector2t<T>::operator=(const Vector3t<T>& v3)
	{
		X = v3.X;
		Y = v3.Y;
		return *this;
	}

	template<typename T>
	Vector2t<T>& Vector2t<T>::operator=(const Vector4t<T>& v4)
	{
		X = v4.X;
		Y = v4.Y;
		return *this;
	}

	////////////////////////////////////////////
	// End Vector2 /////////////////////////////
	////////////////////////////////////////////


	////////////////////////////////////////////
	// Begin Vector3 ///////////////////////////
	////////////////////////////////////////////

	template<typename T>
	Vector3t<T>::Vector3t(const Vector2t<T>& v2)
		: X(v2.X), Y(v2.Y), Z((T)0)
	{}

	template<typename T>
	Vector3t<T>::Vector3t(const Vector4t<T>& v4)
		: X(v4.X), Y(v4.Y), X(v4.Z)
	{}

	template<typename T>
	Vector3t<T>& Vector3t<T>::operator=(const Vector2t<T>& v2)
	{
		X = v2.X;
		Y = v2.Y;
		Z = (T)0;
		return *this;
	}

	template<typename T>
	Vector3t<T>& Vector3t<T>::operator=(const Vector4t<T>& v4)
	{
		X = v4.X;
		Y = v4.Y;
		Z = v4.Z;
		return *this;
	}

	////////////////////////////////////////////
	// End Vector3 /////////////////////////////
	////////////////////////////////////////////


	////////////////////////////////////////////
	// Begin Vector4 ///////////////////////////
	////////////////////////////////////////////

	template<typename T>
	Vector4t<T>::Vector4t(const Vector2t<T>& v2)
		: X(v2.X), Y(v2.Y), Z((T)0), W((T)0)
	{}

	template<typename T>
	Vector4t<T>::Vector4t(const Vector3t<T>& v3)
		: X(v3.X), Y(v3.Y), Z(v3.Z), W((T)0)
	{}

	template<typename T>
	Vector4t<T>& Vector4t<T>::operator=(const Vector2t<T>& v2)
	{
		X = v2.X;
		Y = v2.Y;
		Z = (T)0;
		W = (T)0;
		return *this;
	}

	template<typename T>
	Vector4t<T>& Vector4t<T>::operator=(const Vector3t<T>& v3)
	{
		X = v3.X;
		Y = v3.Y;
		Z = v3.Z;
		W = (T)0;
		return *this;
	}

	////////////////////////////////////////////
	// End Vector4 /////////////////////////////
	////////////////////////////////////////////

}