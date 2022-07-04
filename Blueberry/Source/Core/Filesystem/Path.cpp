// Copyright to Avram Traian. 2022 - 2022.
// File created on July 3 2022.

#include "Path.h"

#include "Filesystem.h"

namespace Blueberry { namespace Filesystem {

	Path::Path()
	{
		m_Data.SetSizeZeroed(1);
	}

	Path::Path(const Path& other)
		: m_Data(other.m_Data)
	{
	}

	Path::Path(Path&& other) noexcept
		: m_Data(Move(other.m_Data))
	{
	}

	Path::Path(PathView other)
	{
		m_Data.SetSizeUninitialized(other.Length() + 1);
		Memory::Copy(m_Data.Data(), other.Data(), other.Length() * sizeof(CharT));
		m_Data[Length()] = 0;
	}

	Path::Path(const CharT* other)
	{
		SizeT other_length = StringCalls_TCHAR::Length(other);
		m_Data.SetSizeUninitialized(other_length + 1);
		Memory::Copy(m_Data.Data(), other, (other_length + 1) * sizeof(CharT));
	}

	Path::Path(const CharT* other, SizeT other_length)
	{
		m_Data.SetSizeUninitialized(other_length + 1);
		Memory::Copy(m_Data.Data(), other, other_length * sizeof(CharT));
		m_Data[Length()] = 0;
	}

	Path::~Path()
	{
		m_Data.SetSizeInternal(0);
	}

	Path& Path::operator=(const Path& other)
	{
		m_Data.SetSizeInternal(0);
		m_Data = other.m_Data;
		return *this;
	}

	Path& Path::operator=(Path&& other) noexcept
	{
		m_Data.SetSizeInternal(0);
		m_Data = Move(other.m_Data);
		return *this;
	}

	Path& Path::operator=(PathView other)
	{
		m_Data.SetSizeInternal(0);
		m_Data.SetSizeUninitialized(other.Length() + 1);
		Memory::Copy(m_Data.Data(), other.Data(), other.Length() * sizeof(CharT));
		m_Data[Length()] = 0;
		return *this;
	}

	Path& Path::operator=(const CharT* other)
	{
		SizeT other_length = StringCalls_TCHAR::Length(other);
		m_Data.SetSizeInternal(0);
		m_Data.SetSizeUninitialized(other_length + 1);
		Memory::Copy(m_Data.Data(), other, (other_length + 1) * sizeof(CharT));
		return *this;
	}

	const CharT* Path::operator*() const
	{
		return CStr();
	}

	bool Path::IsDirectory() const
	{
		for (SizeT index = Length(); index > 0; index--)
		{
			if (m_Data[index - 1] == TEXT('.'))
				return false;
			if (m_Data[index - 1] == TEXT('/'))
				return true;
		}

		return true;
	}

	bool Path::HasExtension() const
	{
		for (SizeT index = Length(); index > 0; index--)
		{
			if (m_Data[index - 1] == TEXT('.'))
				return !(index == 1 || m_Data[index - 2] == TEXT('/'));
			if (m_Data[index - 1] == TEXT('/'))
				return false;
		}

		return false;
	}

	Path Path::Filename() const
	{
		bool is_file = false;
		for (SizeT index = Length(); index > 0; index--)
		{
			if (m_Data[index - 1] == TEXT('.'))
			{
				is_file = true;
			}
			else if (m_Data[index - 1] == TEXT('/'))
			{
				if (is_file)
				{
					return Path(CStr() + index, Length() - index);
				}
				else
				{
					return Path();
				}
			}
		}

		return is_file ? *this : Path();
	}

	Path Path::Extension() const
	{
		for (SizeT index = Length(); index > 0; index--)
		{
			if (m_Data[index - 1] == TEXT('.'))
			{
				if (index == 1 || m_Data[index - 2] == TEXT('/'))
					return Path();
				else
					return Path(CStr() + index - 1, Length() - index + 1);
			}
		}

		return Path();
	}

	Path Path::Stem() const
	{
		SizeT period = BLUE_INVALID_SIZE;

		for (SizeT index = Length(); index > 0; index--)
		{
			if (m_Data[index - 1] == TEXT('.'))
			{
				period = index - 1;
			}
			else if (m_Data[index - 1] == TEXT('/'))
			{
				if (period == BLUE_INVALID_SIZE)
					return Path();
				else
					return Path(CStr() + index, period - index);
			}
		}

		return Path();
	}

	Path Path::Parent() const
	{
		for (SizeT index = Length(); index > 0; index--)
		{
			if (m_Data[index - 1] == TEXT('/'))
				return Path(CStr(), index - 1);
		}

		return *this;
	}

	Path Path::Absolute() const
	{
		return Path();
	}

	String Path::ToString() const
	{
		return String(CStr(), Length());
	}

	StringView Path::ToStringView() const
	{
		return StringView(CStr(), Length());
	}

	PathView::PathView(const Path& other)
		: m_Data(*other)
		, m_Length(other.Length())
	{
	}

	PathView& PathView::operator=(const Path& other)
	{
		m_Data = *other;
		m_Length = other.Length();
		return *this;
	}

} }