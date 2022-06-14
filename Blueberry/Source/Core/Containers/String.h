#pragma once

#include "Core/Base.h"

#include "Vector.h"

namespace Blueberry { namespace StringCalls_TCHAR {

	BLUEBERRY_API BLUE_NODISCARD size_t Length(const TCHAR* string);

	BLUEBERRY_API BLUE_NODISCARD bool Equals(const TCHAR* string_a, const TCHAR* string_b);

} }

namespace Blueberry{

	// Forward declaration
	class String;

	class BLUEBERRY_API StringView
	{
	public:
		StringView(const StringView& other);

		StringView(const String& string);
		
		StringView(const TCHAR* string);

		StringView(const TCHAR* string, SizeT string_length);

	public:
		StringView& operator=(const StringView& other);

		StringView& operator=(const String& string);

		StringView& operator=(const TCHAR* string);

	public:
		const TCHAR* Data() const { return m_Data; }

		const TCHAR* CStr() const { return m_Data; }

		SizeT Length() const { return m_Length; }

		bool IsEmpty() const { return (m_Length == 0); }

	private:
		const TCHAR* m_Data;
		SizeT m_Length;
	};

	class BLUEBERRY_API String
	{
	public:
		String();

		String(const String& other);

		String(String&& other) noexcept;

		String(StringView string_view);

		String(const TCHAR* string);

		String(const TCHAR* string, SizeT string_length);

		~String();

	public:
		String& operator=(const String& other);

		String& operator=(String&& other) noexcept;

		String& operator=(StringView string_view);

		String& operator=(const TCHAR* string);

	public:
		TCHAR* Data() const { return m_Data.Data(); }

		const TCHAR* CStr() const { return m_Data.Data(); }

		SizeT Length() const { return (m_Data.Size() - 1); }

		SizeT Capacity() const { return (m_Data.Capacity() - 1); }

		bool IsEmpty() const { return (Length() == 1); }

	private:
		Vector<TCHAR, HeapAllocator> m_Data;
	};

}