// Copyright to Avram Traian. 2022 - 2022.
// File created on July 3 2022.

#pragma once

#include "Core/CoreMinimal.h"

#include "FilesystemErrorCodes.h"

namespace Blueberry { namespace Filesystem {

	class PathView;
	class Path;

	class BLUEBERRY_API Path
	{
	public:
		Path();

		Path(const Path& other);

		Path(Path&& other) noexcept;

		Path(PathView other);

		Path(const CharT* other);

		Path(const CharT* other, SizeT other_length);

		~Path();

	public:
		Path& operator=(const Path& other);

		Path& operator=(Path&& other) noexcept;

		Path& operator=(PathView other);

		Path& operator=(const CharT* other);

		const CharT* operator*() const;

	public:
		CharT* Data() const { return m_Data.Data(); }

		const CharT* CStr() const { return Data(); }

		SizeT Length() const { return m_Data.Size() - 1; }

		SizeT MaxLength() const { return m_Data.Capacity() - 1; }

		bool IsEmpty() const { return (Length() == 0); }

	public:
		bool IsDirectory() const;

		bool HasExtension() const;

		Path Filename() const;

		Path Extension() const;

		Path Stem() const;

		Path Parent() const;

		Path Absolute() const;

	public:
		String ToString() const;

		StringView ToStringView() const;

	private:
		Vector<CharT> m_Data;
	};

	class BLUEBERRY_API PathView
	{
	public:
		PathView(const PathView& other)
			: m_Data(other.m_Data)
			, m_Length(other.m_Length)
		{}

		PathView(const Path& other);

		PathView(const CharT* other)
			: m_Data(other)
			, m_Length(StringCalls::Length(other))
		{}

		PathView(const CharT* other, SizeT other_length)
			: m_Data(other)
			, m_Length(other_length)
		{}

	public:
		PathView& operator=(const PathView& other)
		{
			m_Data = other.m_Data;
			m_Length = other.m_Length;
			return *this;
		}

		PathView& operator=(const Path& other);

		PathView& operator=(const CharT* other)
		{
			m_Data = other;
			m_Length = StringCalls::Length(other);
			return *this;
		}

		const CharT* operator*() const
		{
			return CStr();
		}

	public:
		const CharT* Data() const { return m_Data; }

		const CharT* CStr() const { return m_Data; }

		SizeT Length() const { return m_Length; }

	private:
		const CharT* m_Data;
		SizeT m_Length;
	};

} }