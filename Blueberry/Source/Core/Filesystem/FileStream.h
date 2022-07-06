#pragma once

#include "FilesystemErrorCodes.h"
#include "Path.h"

namespace Blueberry { namespace Filesystem {

	enum FileFlagsEnum : uint32_t
	{
		FILEFLAGS_None       = 0,
		FILEFLAGS_AppendData = BIT(0)
	};
	using FileFlags = uint32_t;

	class BLUEBERRY_API InputFileStream
	{
	public:
		InputFileStream(FileFlags flags = FILEFLAGS_None);

		InputFileStream(PathView filepath, FileFlags flags = FILEFLAGS_None);

		~InputFileStream();

	public:
		ErrorCode Open(PathView filepath, FileFlags flags = FILEFLAGS_None);

		void Close();

		ErrorCode Read(SizeT file_offset, Vector<ByteT>& out_file_buffer);

		ErrorCode Read(SizeT file_offset, void* out_file_buffer, SizeT file_buffer_size, SizeT* out_written = nullptr);

		ErrorCode ReadText(SizeT file_chars_offset, String& out_text);

	private:
		void* m_NativeFileHandle;
		FileFlags m_FileFlags;
	};

	class BLUEBERRY_API OutputFileStream
	{
	public:
		OutputFileStream(FileFlags flags = FILEFLAGS_None);

		OutputFileStream(PathView filepath, FileFlags flags = FILEFLAGS_None);

		~OutputFileStream();

	public:
		ErrorCode Open(PathView filepath, FileFlags flags = FILEFLAGS_None);

		void Close();

		ErrorCode Write(const void* buffer, SizeT buffer_size, SizeT* out_written = nullptr);
		
		ErrorCode WriteText(StringView text, SizeT* out_written_chars = nullptr);

		void SetFlags(FileFlags new_flags);

	private:
		void* m_NativeFileHandle;
		FileFlags m_FileFlags;
	};

} }