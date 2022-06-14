#pragma once

#include "Core/Base.h"

namespace Blueberry {

	template<typename TypeA, typename TypeB>
	class Pair
	{
	public:
		Pair()
			: A()
			, B()
		{}

		Pair(const Pair& other)
			: A(other.A)
			, B(other.B)
		{}

		Pair(Pair&& other)
			: A(Blueberry::Move(other.A))
			, B(Blueberry::Move(other.B))
		{}

		Pair(const TypeA& a, const TypeB& b)
			: A(a)
			, B(b)
		{}

		Pair(const TypeA& a, TypeB&& b)
			: A(a)
			, B(Blueberry::Move(b))
		{}

		Pair(TypeA&& a, const TypeB& b)
			: A(Blueberry::Move(a))
			, B(b)
		{}

		Pair(TypeA&& a, TypeB&& b)
			: A(Blueberry::Move(a))
			, B(Blueberry::Move(b))
		{}

		~Pair()
		{
		}

	public:
		Pair& operator=(const Pair& other)
		{
			A = other.A;
			B = other.B;
			return *this;
		}

		Pair& operator=(Pair&& other)
		{
			A = Blueberry::Move(other.A);
			B = Blueberry::Move(other.B);
			return *this;
		}

	public:
		TypeA A;
		TypeB B;
	};

}