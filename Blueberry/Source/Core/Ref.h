// Copyright to Avram Traian. 2022 - 2022.
// File created on June 18 2022.

#pragma once

#include "Core/Base.h"
#include "Core/Assert.h"

namespace Blueberry {

	class RefClass
	{
	private:
		uint64_t __GetReferenceCount() const { return m___ReferenceCount; }

		void __IncreaseReferenceCount() { m___ReferenceCount++; }

		bool __DecreaseReferenceCount() { return ((m___ReferenceCount--) <= 1); }

	private:
		uint64_t m___ReferenceCount = 0;

		template<typename T>
		friend class Ref;
	};

	// Forward declaration for Weak<T>.
	// Include 'Weak.h' in order to actually use this type.
	template<typename T>
	class Weak;

	template<typename T>
	class Ref
	{
	public:
		Ref()
			: m_Pointer(nullptr)
		{}

		Ref(const Ref& other)
			: m_Pointer(other.m_Pointer)
		{
			if (m_Pointer)
				m_Pointer->__IncreaseReferenceCount();
		}

		Ref(Ref&& other) noexcept
			: m_Pointer(other.m_Pointer)
		{
			other.m_Pointer = nullptr;
		}

		// Definitions are in 'Weak.h'
		Ref(const Weak<T>& other);
		Ref(Weak<T>&& other);

		Ref(NullptrT)
			: m_Pointer(nullptr)
		{}

		Ref(T* pointer)
			: m_Pointer(pointer)
		{
			if (m_Pointer)
				m_Pointer->__IncreaseReferenceCount();
		}

		~Ref()
		{
			Release();
		}

	public:
		Ref& operator=(const Ref& other)
		{
			if (other.m_Pointer)
				other.m_Pointer->__IncreaseReferenceCount();

			Release();
			m_Pointer = other.m_Pointer;
			return *this;
		}

		Ref& operator=(Ref&& other) noexcept
		{
			Release();
			m_Pointer = other.m_Pointer;
			other.m_Pointer = nullptr;
			return *this;
		}

		// Definitions are in 'Weak.h'
		Ref& operator=(const Weak<T>& other);
		Ref& operator=(Weak<T>&& other);

		Ref& operator=(NullptrT)
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

		bool operator==(const Ref& other) const
		{
			return m_Pointer == other.m_Pointer;
		}

		bool operator==(const Weak<T>& other) const;

		bool operator==(NullptrT) const
		{
			return m_Pointer == nullptr;
		}

		bool operator!=(const Ref& other) const
		{
			return m_Pointer != other.m_Pointer;
		}

		bool operator!=(const Weak<T>& other) const;

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
			if (m_Pointer)
			{
				if (m_Pointer->__DecreaseReferenceCount())
					delete m_Pointer;

				m_Pointer = nullptr;
			}
		}

	private:
		T* m_Pointer;

		template<typename T>
		friend class Weak;
	};

}