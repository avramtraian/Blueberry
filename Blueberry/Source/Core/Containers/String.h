#pragma once

#include "Core/Base.h"

namespace Blueberry { namespace StringCalls_TCHAR {

	BLUEBERRY_API BLUE_NODISCARD size_t Length(const TCHAR* string);

	BLUEBERRY_API BLUE_NODISCARD bool Equals(const TCHAR* string_a, const TCHAR* string_b);

} }

namespace Blueberry{

	class BLUEBERRY_API StringView
	{
	public:
		StringView(const StringView& other)
			: m_Data(other.m_Data)
			, m_Size(other.m_Size)
		{}
		
		StringView(const TCHAR* string)
			: m_Data(string)
			, m_Size(StringCalls_TCHAR::Length(string))
		{}

		StringView(const TCHAR* string, size_t string_length)
			: m_Data(string)
			, m_Size(string_length)
		{}

	public:
		StringView& operator=(const StringView& other)
		{
			m_Data = other.m_Data;
			m_Size = other.m_Size;
			return *this;
		}

		StringView& operator=(const TCHAR* string)
		{

			m_Data = string;
			m_Size = StringCalls_TCHAR::Length(string);
			return *this;
		}

	public:
		const TCHAR* Data() const { return m_Data; }

		const TCHAR* CStr() const { return m_Data; }

		size_t Size() const { return m_Size; }

	private:
		const TCHAR* m_Data;
		size_t m_Size;
	};

}