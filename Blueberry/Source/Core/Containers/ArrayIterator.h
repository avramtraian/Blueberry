// Copyright to Avram Traian. 2022 - 2022.
// File created on June 14 2022.

#pragma once

#include "Core/Base.h"

namespace Blueberry {

	template<typename T>
	class ArrayIterator
	{
	public:
		ArrayIterator(T* pointer)
			: m_Pointer(pointer)
		{}
		
		bool operator==(const ArrayIterator& other) const
		{
			return (m_Pointer == other.m_Pointer);
		}

		bool operator!=(const ArrayIterator& other) const
		{
			return !(*this == other);
		}

		ArrayIterator& operator++()
		{
			m_Pointer++;
			return *this;
		}

		ArrayIterator operator++(int)
		{
			ArrayIterator temp = *this;
			++(*this);
			return temp;
		}

		ArrayIterator& operator--()
		{
			m_Pointer--;
			return *this;
		}

		ArrayIterator operator--(int)
		{
			ArrayIterator temp = *this;
			--(*this);
			return temp;
		}

		T& operator*()
		{
			return *m_Pointer;
		}

		const T& operator*() const
		{
			return *m_Pointer;
		}

		T* operator->()
		{
			return m_Pointer;
		}

		const T* operator->() const
		{
			return m_Pointer;
		}

	private:
		T* m_Pointer;
	};

}