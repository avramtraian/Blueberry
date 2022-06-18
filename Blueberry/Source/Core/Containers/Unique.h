#pragma once

#include "Core/Base.h"
#include "Core/Assert.h"

namespace Blueberry {

	template<typename T>
	class Unique
	{
	public:
		Unique()
			: m_Pointer(nullptr)
		{}

		Unique(const Unique&) = delete;

		Unique(Unique&& other) noexcept
			: m_Pointer(other.m_Pointer)
		{
			other.m_Pointer = nullptr;
		}

		Unique(NullptrT)
			: m_Pointer(nullptr)
		{}

		Unique(T* pointer)
			: m_Pointer(pointer)
		{}

		~Unique()
		{
			Release();
		}

	public:
		Unique& operator=(const Unique&) = delete;

		Unique& operator=(Unique&& other) noexcept
		{
			m_Pointer = other.m_Pointer;
			other.m_Pointer = nullptr;
			return *this;
		}

		Unique& operator=(NullptrT)
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

		bool operator==(const Unique& other) const
		{
			return m_Pointer == other.m_Pointer;
		}

		bool operator==(NullptrT) const
		{
			return m_Pointer == nullptr;
		}

		bool operator!=(const Unique& other) const
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
			if (m_Pointer)
			{
				delete m_Pointer;
				m_Pointer = nullptr;
			}
		}

	private:
		T* m_Pointer;
	};

}