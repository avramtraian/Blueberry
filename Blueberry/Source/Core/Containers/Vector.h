// Copyright to Avram Traian. 2022 - 2022.
// File created on June 14 2022.

#pragma once

#include "Core/Base.h"
#include "Core/Memory.h"

#include "ArrayIterator.h"

#include <initializer_list>

namespace Blueberry {
	
	template<typename ElementType, typename AllocatorType = HeapAllocator>
	class Vector
	{
	public:
		using Iterator             = ArrayIterator<ElementType>;
		using ConstIterator        = ArrayIterator<const ElementType>;
		using ReverseIterator      = ArrayIterator<ElementType>;
		using ReverseConstIterator = ArrayIterator<const ElementType>;

	public:
		Vector()
			: m_Data(nullptr)
			, m_Capacity(0)
			, m_Size(0)
		{}

		Vector(const Vector& other)
			: m_Data(nullptr)
			, m_Capacity(0)
			, m_Size(0)
		{
			CopyConstructor<AllocatorType>(other);
		}

		template<typename OtherAllocatorType>
		Vector(const Vector<ElementType, OtherAllocatorType>& other)
			: m_Data(nullptr)
			, m_Capacity(0)
			, m_Size(0)
		{
			CopyConstructor<OtherAllocatorType>(other);
		}

		Vector(Vector&& other) noexcept
			: m_Data(nullptr)
			, m_Capacity(0)
			, m_Size(0)
		{
			MoveConstructor<AllocatorType>(Blueberry::Move(other));
		}

		template<typename OtherAllocatorType>
		Vector(Vector<ElementType, OtherAllocatorType>&& other) noexcept
			: m_Data(nullptr)
			, m_Capacity(0)
			, m_Size(0)
		{
			MoveConstructor<OtherAllocatorType>(Blueberry::Move(other));
		}

		Vector(std::initializer_list<ElementType> init_list)
			: m_Data(nullptr)
			, m_Capacity(0)
			, m_Size(0)
		{
			SizeT other_size = init_list.size();
			if (other_size == 0)
				return;
			const ElementType* other_data = init_list.begin();
		
			ReAllocate(other_size);
			m_Size = other_size;

			for (SizeT index = 0; index < m_Size; index++)
			{
				new (m_Data + index) ElementType(other_data[index]);
			}
		}

		Vector(const ElementType* elements, SizeT elements_num)
			: m_Data(nullptr)
			, m_Capacity(0)
			, m_Size(0)
		{
			if (elements_num == 0)
				return;

			ReAllocate(elements_num);
			m_Size = elements_num;

			for (SizeT index = 0; index < m_Size; index++)
			{
				new (m_Data + index) ElementType(elements[index]);
			}
		}

		Vector(SizeT initial_capacity)
			: m_Data(nullptr)
			, m_Capacity(0)
			, m_Size(0)
		{
			if (initial_capacity == 0)
				return;

			ReAllocate(initial_capacity);
		}

		~Vector()
		{
			Clear();
			FreeData();
		}

	public:
		Vector& operator=(const Vector& other)
		{
			CopyOperator<AllocatorType>(other);
			return *this;
		}

		template<typename OtherAllocatorType>
		Vector& operator=(const Vector<ElementType, OtherAllocatorType>& other)
		{
			CopyOperator<OtherAllocatorType>(other);
			return *this;
		}

		Vector& operator=(Vector&& other) noexcept
		{
			MoveOperator<AllocatorType>(Blueberry::Move(other));
			return *this;
		}

		template<typename OtherAllocatorType>
		Vector& operator=(Vector<ElementType, OtherAllocatorType>&& other) noexcept
		{
			MoveOperator<OtherAllocatorType>(Blueberry::Move(other));
			return *this;
		}

		Vector& operator=(std::initializer_list<ElementType> init_list)
		{
			Clear();

			SizeT other_size = init_list.size();
			if (other_size == 0)
				return;
			const ElementType* other_data = init_list.begin();

			if (other_size > m_Capacity)
				ReAllocate(NextCapacity(m_Capacity));
			m_Size = other_size;

			for (SizeT index = 0; index < m_Size; index++)
			{
				new (m_Data + index) ElementType(other_data[index]);
			}

			return *this;
		}

		ElementType& operator[](SizeT index)
		{
			return m_Data[index];
		}

		const ElementType& operator[](SizeT index) const
		{
			return m_Data[index];
		}

		Vector& operator+=(const Vector& other)
		{
			return Append<AllocatorType>(other);
		}

		template<typename OtherAllocatorType>
		Vector& operator+=(const Vector<ElementType, OtherAllocatorType>& other)
		{
			return Append<OtherAllocatorType>(other);
		}

		Vector& operator+=(Vector&& other)
		{
			return Append<AllocatorType>(Blueberry::Move(other));
		}

		template<typename OtherAllocatorType>
		Vector& operator+=(Vector<ElementType, OtherAllocatorType>&& other)
		{
			return Append<OtherAllocatorType>(Blueberry::Move(other));
		}
		
		Vector& operator+=(std::initializer_list<ElementType> to_append)
		{
			return Append(to_append, false);
		}

		bool operator==(const Vector& other) const
		{
			if (m_Size != other.m_Size)
				return false;

			for (SizeT index = 0; index < m_Size; index++)
			{
				if (m_Data[index] != other.m_Data[index])
					return false;
			}

			return true;
		}

		template<typename OtherAllocatorType>
		bool operator==(const Vector<ElementType, OtherAllocatorType>& other) const
		{
			if (m_Size != other.m_Size)
				return false;

			for (SizeT index = 0; index < m_Size; index++)
			{
				if (m_Data[index] != other.m_Data[index])
					return false;
			}

			return true;
		}

		bool operator!=(const Vector& other) const
		{
			return !(*this == other);
		}

		template<typename OtherAllocatorType>
		bool operator!=(const Vector<ElementType, OtherAllocatorType>& other) const
		{
			return !(*this == other);
		}

	public:
		ElementType* Data() const { return m_Data; }

		SizeT Capacity() const { return m_Capacity; }

		SizeT Size() const { return m_Size; }

		bool IsEmpty() const { return (m_Size == 0); }

	public:
		ElementType& Add(const ElementType& element)
		{
			if (m_Size >= m_Capacity)
				ReAllocate(m_Capacity + m_Capacity / 2 + 1);

			new (m_Data + m_Size) ElementType(element);
			return m_Data[m_Size++];
		}

		ElementType& Add(ElementType&& element)
		{
			if (m_Size >= m_Capacity)
				ReAllocate(m_Capacity + m_Capacity / 2 + 1);

			new (m_Data + m_Size) ElementType(Blueberry::Move(element));
			return m_Data[m_Size++];
		}

		SizeT AddDefaulted(SizeT num)
		{
			if (num == 0)
				return BLUE_INVALID_SIZE;

			if (m_Size + num > m_Capacity)
				ReAllocate(NextCapacity(m_Size + num));

			for (SizeT index = m_Size; index < m_Size + num; index++)
				new (m_Data + index) ElementType();

			m_Size += num;
			return m_Size - num;
		}

		ElementType& AddDefaulted()
		{
			SizeT index = AddDefaulted(1);
			return m_Data[index];
		}

		SizeT AddZeroed(SizeT num)
		{
			if (num == 0)
				return BLUE_INVALID_SIZE;

			if (m_Size + num > m_Capacity)
				ReAllocate(NextCapacity(m_Size + num));

			Memory::Zero(m_Data + m_Size, num * sizeof(ElementType));

			m_Size += num;
			return m_Size - num;
		}

		ElementType& AddZeroed()
		{
			SizeT index = AddZeroed(1);
			return m_Data[index];
		}

		SizeT AddUninitialized(SizeT num)
		{
			if (num == 0)
				return BLUE_INVALID_SIZE;

			if (m_Size + num > m_Capacity)
				ReAllocate(NextCapacity(m_Size + num));

			m_Size += num;
			return m_Size - num;
		}

		ElementType& AddUninitialized()
		{
			SizeT index = AddUninitialized(1);
			return m_Data[index];
		}

		template<typename... Args>
		ElementType& Emplace(Args&&... args)
		{
			if (m_Size >= m_Capacity)
				ReAllocate(m_Capacity + m_Capacity / 2 + 1);

			new (m_Data + m_Size) ElementType(Blueberry::Forward<Args>(args)...);
			return m_Data[m_Size++];
		}

		void Pop()
		{
			m_Data[m_Size - 1].~ElementType();
			m_Size--;
		}

		void Remove(SizeT location)
		{
			ShiftElementsLeft(location, 1);
			m_Size--;
		}

		ElementType& Front()
		{
			return m_Data[0];
		}

		const ElementType& Front() const
		{
			return m_Data[0];
		}

		ElementType& Back()
		{
			return m_Data[m_Size - 1];
		}

		const ElementType& Back() const
		{
			return m_Data[m_Size - 1];
		}

		Vector& Append(const ElementType* elements, SizeT elements_num, bool move_elements = false)
		{
			if (m_Size + elements_num > m_Capacity)
				ReAllocate(NextCapacity(m_Size + elements_num));

			if (move_elements)
			{
				for (SizeT index = m_Size; index < m_Size + elements_num; index++)
					new (m_Data + index) ElementType(Blueberry::Move(elements[index]));
			}
			else
			{
				for (SizeT index = m_Size; index < m_Size + elements_num; index++)
					new (m_Data + index) ElementType(elements[index]);
			}

			m_Size += elements_num;

			return *this;
		}

		template<typename OtherAllocatorType>
		Vector& Append(const Vector<ElementType, OtherAllocatorType>& to_append)
		{
			return Append(to_append.m_Data, to_append.m_Size, false);
		}

		template<typename OtherAllocatorType>
		Vector& Append(Vector<ElementType, OtherAllocatorType>&& to_append)
		{
			return Append(to_append.m_Data, to_append.m_Size, true);
		}

		Vector& Append(std::initializer_list<ElementType> to_append, bool move_elements = false)
		{
			return Append(to_append.begin(), to_append.size(), move_elements);
		}

		void Insert(SizeT location, const ElementType& element)
		{
			Insert(location, &element, 1, false);
		}

		void Insert(SizeT location, ElementType&& element)
		{
			Insert(location, &element, 1, true);
		}

		void Insert(SizeT location, const ElementType* elements, SizeT elements_num, bool move_elements = false)
		{
			if (elements_num == 0)
				return;

			if (m_Size + elements_num > m_Capacity)
				ReAllocate(NextCapacity(m_Size + elements_num));

			ShiftElementsRight(location, elements_num);

			if (move_elements)
			{
				for (SizeT index = 0; index < elements_num; index++)
					new (m_Data + location + index) ElementType(Blueberry::Move(elements[index]));
			}
			else
			{
				for (SizeT index = 0; index < elements_num; index++)
					new (m_Data + location + index) ElementType(elements[index]);
			}

			m_Size += elements_num;
		}

		void Insert(SizeT location, std::initializer_list<ElementType> init_list, bool move_elements = false)
		{
			Insert(location, init_list.begin(), init_list.size(), move_elements);
		}

		void InsertDefaulted(SizeT location, SizeT num)
		{
			if (num == 0)
				return;

			if (m_Size + num > m_Capacity)
				ReAllocate(NextCapacity(m_Size + num));

			ShiftElementsRight(location, num);

			for (SizeT index = 0; index < num; index++)
					new (m_Data + location + index) ElementType();

			m_Size += num;
		}

		void InsertZeroed(SizeT location, SizeT num)
		{
			if (num == 0)
				return;

			if (m_Size + num > m_Capacity)
				ReAllocate(NextCapacity(m_Size + num));

			ShiftElementsRight(location, num);

			Memory::Zero(m_Data + location, num * sizeof(ElementType));

			m_Size += num;
		}

		void InsertUninitialized(SizeT location, SizeT num)
		{
			if (num == 0)
				return;

			if (m_Size + num > m_Capacity)
				ReAllocate(NextCapacity(m_Size + num));

			ShiftElementsRight(location, num);

			m_Size += num;
		}

	public:
		void SetSize(SizeT new_size)
		{
			if (new_size == m_Size)
				return;

			if (new_size > m_Capacity)
				ReAllocate(NextCapacity(new_size));

			for (SizeT index = m_Size; index < new_size; index++)
				new (m_Data + index) ElementType();

			for (SizeT index = new_size; index < m_Size; index++)
				m_Data[index].~ElementType();

			m_Size = new_size;
		}

		void SetSizeZeroed(SizeT new_size)
		{
			if (new_size == m_Size)
				return;

			if (new_size > m_Capacity)
				ReAllocate(NextCapacity(new_size));

			if (new_size > m_Size)
				Memory::Zero(m_Data + m_Size, (new_size - m_Size) * sizeof(ElementType));

			for (SizeT index = new_size; index < m_Size; index++)
				m_Data[index].~ElementType();

			m_Size = new_size;
		}

		void SetSizeUninitialized(SizeT new_size)
		{
			if (new_size == m_Size)
				return;

			if (new_size > m_Capacity)
				ReAllocate(NextCapacity(new_size));

			for (SizeT index = new_size; index < m_Size; index++)
				m_Data[index].~ElementType();

			m_Size = new_size;
		}

		void SetSizeInternal(SizeT new_size)
		{
			m_Size = new_size;
		}

		void SetCapacity(SizeT new_capacity)
		{
			if (new_capacity == m_Capacity)
				return;

			ReAllocate(new_capacity);
		}

		void Clear()
		{
			for (SizeT index = 0; index < m_Size; index++)
				m_Data[index].~ElementType();

			m_Size = 0;
		}

	private:
		void ReAllocate(SizeT new_capacity)
		{
			ElementType* new_block = (ElementType*)m_AllocatorInstance.AllocateTagged(new_capacity * sizeof(ElementType));

			if (m_Size > new_capacity)
			{
				for (SizeT index = new_capacity; index < m_Size; index++)
					m_Data[index].~ElementType();

				m_Size = new_capacity;
			}

			for (SizeT index = 0; index < m_Size; index++)
			{
				new (new_block + index) ElementType(Blueberry::Move(m_Data[index]));
				m_Data[index].~ElementType();
			}

			FreeData();

			m_Data = new_block;
			m_Capacity = new_capacity;
		}

		void FreeData()
		{
			m_AllocatorInstance.Free(m_Data, m_Capacity * sizeof(ElementType));

			m_Data = nullptr;
			m_Capacity = 0;
		}

		BLUE_FORCEINLINE SizeT NextCapacity(SizeT required_new_cap)
		{
			SizeT default_new_cap = m_Capacity + m_Capacity / 2 + 1;
			return default_new_cap < required_new_cap ? required_new_cap : default_new_cap;
		}

		template<typename OtherAllocatorType>
		void CopyConstructor(const Vector<ElementType, OtherAllocatorType>& other)
		{
			if (other.IsEmpty())
				return;

			ReAllocate(other.m_Size);
			m_Size = other.m_Size;

			for (SizeT index = 0; index < m_Size; index++)
				new (m_Data + index) ElementType(other.m_Data[index]);
		}

		template<typename OtherAllocatorType>
		void MoveConstructor(Vector<ElementType, OtherAllocatorType>&& other)
		{
			if (CompareAllocators(m_AllocatorInstance, other.m_AllocatorInstance))
			{
				m_Data = other.m_Data;
				m_Capacity = other.m_Capacity;
				m_Size = other.m_Size;

				other.m_Data = nullptr;
				other.m_Capacity = 0;
			}
			else
			{
				ReAllocate(other.m_Size);
				m_Size = other.m_Size;

				for (SizeT index = 0; index < m_Size; index++)
				{
					new (m_Data + index) ElementType(Blueberry::Move(other.m_Data[index]));
					other.m_Data[index].~ElementType();
				}
			}

			other.m_Size = 0;
		}

		template<typename OtherAllocatorType>
		void CopyOperator(const Vector<ElementType, OtherAllocatorType>& other)
		{
			Clear();

			if (other.IsEmpty())
				return;

			if (other.m_Size > m_Capacity)
				ReAllocate(NextCapacity(other.m_Size));
			m_Size = other.m_Size;

			for (SizeT index = 0; index < m_Size; index++)
				new (m_Data + index) ElementType(other.m_Data[index]);
		}

		template<typename OtherAllocatorType>
		void MoveOperator(Vector<ElementType, OtherAllocatorType>&& other)
		{
			Clear();

			if (CompareAllocators(m_AllocatorInstance, other.m_AllocatorInstance))
			{
				ElementType* temp_data = m_Data;
				SizeT temp_capacity = m_Capacity;

				m_Data = other.m_Data;
				m_Capacity = other.m_Capacity;
				m_Size = other.m_Size;

				other.m_Data = temp_data;
				other.m_Capacity = temp_capacity;
			}
			else
			{
				if (other.m_Size > m_Capacity)
					ReAllocate(NextCapacity(other.m_Size));
				m_Size = other.m_Size;

				for (SizeT index = 0; index < m_Size; index++)
				{
					new (m_Data + index) ElementType(Blueberry::Move(other.m_Data[index]));
					other.m_Data[index].~ElementType();
				}
			}

			other.m_Size = 0;
		}

		void ShiftElementsRight(SizeT starting_index, SizeT offset)
		{
			if (m_Size == starting_index)
				return;

			SizeT moved_num = m_Size - starting_index - offset;

			for (SizeT index = m_Size; index < m_Size + offset; index++)
			{
				new (m_Data + index) ElementType(Blueberry::Move(m_Data[index - offset]));
			}
			for (SizeT index = 0; index < moved_num; index++)
			{
				m_Data[m_Size - index - 1] = Blueberry::Move(m_Data[m_Size - index - offset - 1]);
			}
			for (SizeT index = starting_index; index < starting_index + offset; index++)
			{
				m_Data[index].~ElementType();
			}
		}

		void ShiftElementsLeft(SizeT starting_index, SizeT offset)
		{
			if (m_Size == starting_index)
				return;

			for (SizeT index = starting_index - offset; index < m_Size - offset - 1; index++)
			{
				m_Data[index] = Blueberry::Move(m_Data[index + offset]);
			}
			for (SizeT index = m_Size - offset - 1; index < m_Size - 1; index++)
			{
				m_Data[index].~ElementType();
			}
		}

	public:
		Iterator begin() { return Iterator(m_Data); }

		Iterator end() { return Iterator(m_Data + m_Size); }

		ConstIterator begin() const { return ConstIterator(m_Data); }

		ConstIterator end() const { return ConstIterator(m_Data + m_Size); }

		ReverseIterator rbegin() { return ReverseIterator(m_Data + m_Size - 1); }

		ReverseIterator rend() { return ReverseIterator(m_Data - 1); }

		ReverseConstIterator rbegin() const { return ReverseConstIterator(m_Data + m_Size - 1); }

		ReverseConstIterator rend() const { return ReverseConstIterator(m_Data - 1); }

	private:
		ElementType* m_Data;

		SizeT m_Capacity;

		SizeT m_Size;

		AllocatorType m_AllocatorInstance;
	};

}