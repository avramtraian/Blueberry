// Copyright to Avram Traian. 2022 - 2022.
// File created on July 3 2022.

#if BLUE_PLATFORM_WINDOWS

#include "WindowsHeaders.h"

#include "Core/Filesystem/Filesystem.h"
#include "Core/Filesystem/FileStream.h"

namespace Blueberry { namespace Filesystem {

	struct WindowsFilesystemData
	{
		Path WorkingDirectory;
	};
	static WindowsFilesystemData* s_Filesystem = nullptr;

	bool Initialize()
	{
		if (s_Filesystem)
			return false;

		s_Filesystem = bbnew WindowsFilesystemData();
		if (!s_Filesystem)
			return false;

		CharT wd_buffer[512];
		SizeT wd_length = (SizeT)GetCurrentDirectory(BLUE_ARRAY_LENGTH(wd_buffer), wd_buffer);
		if (wd_length == 0)
			return false;

		s_Filesystem->WorkingDirectory = Path(wd_buffer, wd_length);

		return true;
	}

	void Shutdown()
	{
		if (!s_Filesystem)
			return;

		delete s_Filesystem;
		s_Filesystem = nullptr;
	}

	const Path& GetWorkingDirectory()
	{
		return s_Filesystem->WorkingDirectory;
	}

	void SetWorkingDirectory(PathView new_working_directory)
	{
		s_Filesystem->WorkingDirectory = new_working_directory;
		BLUE_CORE_VERIFY(SetCurrentDirectory(*s_Filesystem->WorkingDirectory));
	}

	ErrorCode FileDelete(PathView filepath)
	{
		// Deletes the file.
		BOOL result = DeleteFile(*filepath);

		// Checks for any errors.
		if (result == FALSE)
		{
			switch (GetLastError())
			{
				case ERROR_FILE_NOT_FOUND: return FILESYSTEM_ERROR_FILE_NOT_FOUND;
			}
		}

		// Success.
		return FILESYSTEM_ERROR_NONE;
	}

	ErrorCode FileCopy(PathView src_filepath, PathView dest_filepath)
	{
		// Copies the file.
		BOOL result = CopyFile(*src_filepath, *dest_filepath, true);

		// Checks for any errors.
		if (result == FALSE)
		{
			switch (GetLastError())
			{
				case ERROR_FILE_NOT_FOUND: return FILESYSTEM_ERROR_FILE_NOT_FOUND;
			}
		}

		// Success.
		return FILESYSTEM_ERROR_NONE;
	}

	ErrorCode FileMove(PathView src_filepath, PathView dest_filepath)
	{
		// Moves the file.
		BOOL result = MoveFile(*src_filepath, *dest_filepath);

		// Checks for any errors.
		if (result == FALSE)
		{
			switch (GetLastError())
			{
				case ERROR_FILE_NOT_FOUND: return FILESYSTEM_ERROR_FILE_NOT_FOUND;
			}
		}

		// Success.
		return FILESYSTEM_ERROR_NONE;
	}

	ErrorCode FileRename(const Path& filepath, StringView new_filename)
	{
		// TODO:
		return FILESYSTEM_ERROR_NONE;
	}

	InputFileStream::InputFileStream(FileFlags flags /*= FILEFLAGS_None*/)
		: m_NativeFileHandle(INVALID_HANDLE_VALUE)
		, m_FileFlags(flags)
	{
	}

	InputFileStream::InputFileStream(PathView filepath, FileFlags flags /*= FILEFLAGS_None*/)
		: m_NativeFileHandle(INVALID_HANDLE_VALUE)
		, m_FileFlags(flags)
	{
		Open(filepath, flags);
	}

	InputFileStream::~InputFileStream()
	{
		Close();
	}

	ErrorCode InputFileStream::Open(PathView filepath, FileFlags flags /*= FILEFLAGS_None*/)
	{
		// Closing the old file handle (if exists).
		if (m_NativeFileHandle != INVALID_HANDLE_VALUE)
		{
			Close();
		}

		// Setting the Win32 file creation flags.
		DWORD access_flags   = FILE_READ_DATA;
		DWORD share_mode     = 0;
		DWORD creation_flags = OPEN_EXISTING;

		// Creating the file handle.
		HANDLE file_handle = CreateFile(
			*filepath,
			access_flags,
			share_mode,
			NULL,
			creation_flags,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		// Checking for any errors.
		if (file_handle == INVALID_HANDLE_VALUE)
		{
			switch (GetLastError())
			{
				// Invalid filepath passed.
				case ERROR_FILE_NOT_FOUND:    return FILESYSTEM_ERROR_FILE_NOT_FOUND;

				// File is already opened.
				case ERROR_SHARING_VIOLATION: return FILESYSTEM_ERROR_FILE_IN_USE;
			}
		}

		m_NativeFileHandle = file_handle;
		return FILESYSTEM_ERROR_NONE;
	}

	void InputFileStream::Close()
	{
		// Checking if the file handle is valid.
		if (m_NativeFileHandle == INVALID_HANDLE_VALUE)
			return;

		// Closing the file handle.
		CloseHandle((HANDLE)m_NativeFileHandle);
		m_NativeFileHandle = INVALID_HANDLE_VALUE;
	}

	ErrorCode InputFileStream::Read(SizeT file_offset, Vector<ByteT>& out_file_buffer)
	{
		out_file_buffer.Clear();

		// Checks that the stream is opened.
		if (m_NativeFileHandle == INVALID_HANDLE_VALUE)
		{
			return FILESYSTEM_ERROR_INVALID_HANDLE;
		}

		// Gets the file size.
		LARGE_INTEGER li_filesize;
		GetFileSizeEx(m_NativeFileHandle, &li_filesize);
		SizeT filesize = li_filesize.QuadPart;

		// Prepares the buffer for writing to it.
		out_file_buffer.SetSizeUninitialized(filesize);

		// Reads the file.
		OVERLAPPED overlapped = {};
		overlapped.Offset     = (file_offset << 32) >> 32;
		overlapped.OffsetHigh = (file_offset >> 32);
		DWORD written;
		BOOL result = ReadFile(m_NativeFileHandle, out_file_buffer.Data(), (DWORD)filesize, &written, &overlapped);

		// Checks for any errors.
		if (result == FALSE)
		{
			switch (GetLastError())
			{
				case ERROR_INVALID_USER_BUFFER: return FILESYSTEM_ERROR_BUFFER_OVERFLOW;
			}
		}

		return FILESYSTEM_ERROR_NONE;
	}

	ErrorCode InputFileStream::Read(SizeT file_offset, void* out_file_buffer, SizeT file_buffer_size, SizeT& out_written)
	{
		out_written = 0;

		// Checks that the stream is opened.
		if (m_NativeFileHandle == INVALID_HANDLE_VALUE)
		{
			return FILESYSTEM_ERROR_INVALID_HANDLE;
		}

		// Reads the file.
		OVERLAPPED overlapped = {};
		overlapped.Offset     = (file_offset << 32) >> 32;
		overlapped.OffsetHigh = (file_offset >> 32);
		DWORD written;
		BOOL result = ReadFile(m_NativeFileHandle, out_file_buffer, (DWORD)file_buffer_size, &written, &overlapped);

		// Checks for any errors.
		if (result == FALSE)
		{
			switch (GetLastError())
			{
				case ERROR_INVALID_USER_BUFFER: return FILESYSTEM_ERROR_BUFFER_OVERFLOW;
			}
		}

		out_written = (SizeT)written;
		return FILESYSTEM_ERROR_NONE;
	}

} }

#endif