// Copyright to Avram Traian. 2022 - 2022.
// File created on June 15 2022.

#pragma once

#include "Core/Base.h"
#include "ArrayIterator.h"

namespace Blueberry {
	
	/**
	* Blueberry Array Container.
	*/
	template<typename T, SizeT S>
	class Array
	{
	public:
		// Iterator typedefs
		using Iterator             = ArrayIterator<T>;
		using ConstIterator        = ArrayIterator<const T>;
		using ReverseIterator      = ArrayIterator<T>;
		using ReverseConstIterator = ArrayIterator<const T>;

	public:
		/**
		* Default constructor.
		* Initializes all the elements with their default constructor.
		*/
		Array()
			: m_Data{}
		{}

		/**
		* Copy constructor.
		* 
		* @param other Array to copy.
		*/
		Array(const Array& other)
		{
			for (SizeT index = 0; index < S; index++)
				m_Data[index] = other.m_Data[index];
		}

		/**
		* Move constructor.
		*
		* @param other Array to move.
		*/
		Array(Array&& other) noexcept
		{
			for (SizeT index = 0; index < S; index++)
				m_Data[index] = Blueberry::Move(other.m_Data[index]);
		}

		/**
		* Deconstructor.
		*/
		~Array() = default;

	public:
		/**
		* Copy assign operator.
		* 
		* @param other Array to copy.
		* 
		* @returns A reference to this.
		*/
		Array& operator=(const Array& other)
		{
			for (SizeT index = 0; index < S; index++)
				m_Data[index] = other.m_Data[index];

			return *this;
		}

		/**
		* Move assign operator.
		*
		* @param other Array to move.
		*
		* @returns A reference to this.
		*/
		Array& operator=(Array&& other) noexcept
		{
			for (SizeT index = 0; index < S; index++)
				m_Data[index] = Blueberry::Move(other.m_Data[index]);

			return *this;
		}

		/**
		* Index operator.
		* 
		* @param index The index of the element.
		* 
		* @returns Reference to the element found at the specified index.
		*/
		T& operator[](SizeT index)
		{
			return m_Data[index];
		}

		/**
		* Index operator.
		* Const version of the above.
		*
		* @param index The index of the element.
		*
		* @returns Reference to the element found at the specified index.
		*/
		const T& operator[](SizeT index) const
		{
			return m_Data[index];
		}

	public:
		/**
		* Gets a pointer to the first element in the array.
		* 
		* @returns Pointer to the array.
		*/
		T* Data() const { return (T*)(&m_Data[0]); }

		/**
		* Gets the size of the array.
		* 
		* @returns The size of the array.
		*/
		static constexpr SizeT Size() { return S; }

	public:
		// Iterators

		Iterator IteratorAt(SizeT index) { return Iterator(m_Data + index); }

		ConstIterator IteratorAt(SizeT index) const { ConstIterator Iterator(m_Data + index); }

		Iterator begin() { return IteratorAt(0); }

		Iterator end() { return IteratorAt(S); }

		ConstIterator begin() const { return IteratorAt(0); }

		ConstIterator end() const { return IteratorAt(S); }

		ReverseIterator rbegin() { return ReverseIterator(m_Data + S - 1); }

		ReverseIterator rend() { return ReverseIterator(m_Data - 1); }

		ReverseConstIterator rbegin() const { return ReverseConstIterator(m_Data + S - 1); }

		ReverseConstIterator rend() const { return ReverseConstIterator(m_Data - 1); }

	private:
		// The array.
		T m_Data[S];
	};

}