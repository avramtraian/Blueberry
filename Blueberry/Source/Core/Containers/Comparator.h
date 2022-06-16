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
	struct Comparator<const TCHAR*>
	{
		static bool Compare(const TCHAR* const& a, const TCHAR* const& b)
		{
			const TCHAR* string_a = a;
			const TCHAR* string_b = b;

			while (*(string_a++) && *(string_b++))
			{
				if (*string_a != *string_b)
					return false;
			}
			return (*string_a == *string_b);
		}
	};

}