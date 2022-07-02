// Copyright to Avram Traian. 2022 - 2022.
// File created on June 16 2022.

#pragma once

#include "Core/Base.h"

namespace Blueberry {

	template<typename T>
	struct Comparator
	{
		static bool Compare(const T& a, const T& b)
		{
			return (a == b);
		}
	};

	template<>
	struct Comparator<const CharT*>
	{
		static bool Compare(const CharT* const& a, const CharT* const& b)
		{
			const CharT* string_a = a;
			const CharT* string_b = b;

			while (*(string_a++) && *(string_b++))
			{
				if (*string_a != *string_b)
					return false;
			}
			return (*string_a == *string_b);
		}
	};

}