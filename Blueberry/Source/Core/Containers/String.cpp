#include "String.h"

namespace Blueberry { namespace StringCalls_TCHAR {

	size_t Length(const TCHAR* string)
	{
		const TCHAR* first = string;
		while (*(string++));
		return string - first - 1;
	}

	bool Equals(const TCHAR* string_a, const TCHAR* string_b)
	{
		while (*(string_a++) && *(string_b++))
		{
			if (*string_a != *string_b)
				return false;
		}
		return (*string_a == *string_b);
	}

} }