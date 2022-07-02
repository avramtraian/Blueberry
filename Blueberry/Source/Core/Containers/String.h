// Copyright to Avram Traian. 2022 - 2022.
// File created on June 13 2022.

#pragma once

#include "Core/Base.h"

#include "Vector.h"

namespace Blueberry { namespace StringCalls_TCHAR {

	BLUEBERRY_API BLUE_NODISCARD size_t Length(const CharT* string);

	BLUEBERRY_API BLUE_NODISCARD bool Equals(const CharT* string_a, const CharT* string_b);

} }

namespace Blueberry{

	// Forward declaration
	class String;

	class BLUEBERRY_API StringView
	{
	public:
		StringView(const StringView& other);

		StringView(const String& string);
		
		StringView(const CharT* string);

		StringView(const CharT* string, SizeT string_length);

	public:
		StringView& operator=(const StringView& other);

		StringView& operator=(const String& string);

		StringView& operator=(const CharT* string);

		const CharT* operator*() const;

	public:
		const CharT* Data() const { return m_Data; }

		const CharT* CStr() const { return m_Data; }

		SizeT Length() const { return m_Length; }

		bool IsEmpty() const { return (m_Length == 0); }

	private:
		const CharT* m_Data;
		SizeT m_Length;
	};

	class BLUEBERRY_API String
	{
	public:
		String();

		String(const String& other);

		String(String&& other) noexcept;

		String(StringView string_view);

		String(const CharT* string);

		String(const CharT* string, SizeT string_length);

		~String();

	public:
		String& operator=(const String& other);

		String& operator=(String&& other) noexcept;

		String& operator=(StringView string_view);

		String& operator=(const CharT* string);

		const CharT* operator*() const;

	public:
		CharT* Data() const { return m_Data.Data(); }

		const CharT* CStr() const { return m_Data.Data(); }

		SizeT Length() const { return (m_Data.Size() - 1); }

		SizeT Capacity() const { return (m_Data.Capacity() - 1); }

		bool IsEmpty() const { return (Length() == 1); }

	private:
		Vector<CharT, HeapAllocator> m_Data;
	};

}