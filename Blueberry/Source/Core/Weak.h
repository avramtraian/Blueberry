// Copyright to Avram Traian. 2022 - 2022.
// File created on June 18 2022.

#pragma once

#include "Ref.h"

namespace Blueberry {

	template<typename T>
	class Weak
	{
	public:
		Weak()
			: m_Pointer(nullptr)
		{}

		Weak(const Weak& other)
			: m_Pointer(other.m_Pointer)
		{}

		Weak(Weak&& other)
			: m_Pointer(other.m_Pointer)
		{
			other.m_Pointer = nullptr;
		}

		Weak(const Ref<T>& other)
			: m_Pointer(other.m_Pointer)
		{}

		Weak(NullptrT)
			: m_Pointer(nullptr)
		{}

		~Weak()
		{
		}

	public:
		Weak& operator=(const Weak& other)
		{
			m_Pointer = other.m_Pointer;
			return *this;
		}

		Weak& operator=(Weak&& other)
		{
			m_Pointer = other.m_Pointer;
			other.m_Pointer = nullptr;
			return *this;
		}

		Weak& operator=(const Ref<T>& other)
		{
			m_Pointer = other.m_Pointer;
			return *this;
		}

		Weak& operator=(NullptrT)
		{
			Release();
			return *this;
		}

		T* operator->()
		{
			BLUE_CORE_ASSERT(m_Pointer != nullptr);
			return m_Pointer;
		}

		const T* operator->() const
		{
			BLUE_CORE_ASSERT(m_Pointer != nullptr);
			return m_Pointer;
		}

		T& operator*()
		{
			BLUE_CORE_ASSERT(m_Pointer != nullptr);
			return *m_Pointer;
		}

		const T& operator*() const
		{
			BLUE_CORE_ASSERT(m_Pointer != nullptr);
			return *m_Pointer;
		}

		bool operator==(const Weak& other) const
		{
			return m_Pointer == other.m_Pointer;
		}

		bool operator==(const Ref<T>& other) const
		{
			return m_Pointer == other.m_Pointer;
		}

		bool operator==(NullptrT) const
		{
			return m_Pointer == nullptr;
		}

		bool operator!=(const Weak& other) const
		{
			return m_Pointer != other.m_Pointer;
		}

		bool operator!=(const Ref<T>& other) const
		{
			return m_Pointer != other.m_Pointer;
		}

		bool operator!=(NullptrT) const
		{
			return m_Pointer != nullptr;
		}

	public:
		T* Get() { return m_Pointer; }

		const T* Get() const { return m_Pointer; }

		bool IsValid() const { return (m_Pointer != nullptr); }

		void Release()
		{
			m_Pointer = nullptr;
		}

	private:
		T* m_Pointer;

		template<typename T>
		friend class Ref;
	};

	template<typename T>
	Ref<T>::Ref(const Weak<T>& other)
		: m_Pointer(other.m_Pointer)
	{
		if (m_Pointer)
			m_Pointer->__IncreaseReferenceCount();
	}

	template<typename T>
	Ref<T>::Ref(Weak<T>&& other)
		: m_Pointer(other.m_Pointer)
	{
		other.m_Pointer = nullptr;

		if (m_Pointer)
			m_Pointer->__IncreaseReferenceCount();
	}

	template<typename T>
	Ref<T>& Ref<T>::operator=(const Weak<T>& other)
	{
		Release();
		m_Pointer = other.m_Pointer;
		if (m_Pointer)
			m_Pointer->__IncreaseReferenceCount();

		return *this;
	}

	template<typename T>
	Ref<T>& Ref<T>::operator=(Weak<T>&& other)
	{
		Release();
		m_Pointer = other.m_Pointer;
		if (m_Pointer)
			m_Pointer->__IncreaseReferenceCount();
	
		other.m_Pointer = nullptr;
		return *this;
	}

	template<typename T>
	bool Ref<T>::operator==(const Weak<T>& other) const
	{
		return m_Pointer == other.m_Pointer;
	}

	template<typename T>
	bool Ref<T>::operator!=(const Weak<T>& other) const
	{
		return m_Pointer != other.m_Pointer;
	}

}