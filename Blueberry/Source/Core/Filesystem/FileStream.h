#pragma once

#include "FilesystemErrorCodes.h"
#include "Path.h"

namespace Blueberry { namespace Filesystem {

	class BLUEBERRY_API InputFileStream
	{
	public:
		enum FileFlagsEnum : uint32_t
		{
			FILEFLAGS_None            = 0,
			FILEFLAGS_CreateIfMissing = 1 << 0
		};
		using FileFlags = uint32_t;

	public:
		InputFileStream(FileFlags flags = FILEFLAGS_None);

		InputFileStream(PathView filepath, FileFlags flags = FILEFLAGS_None);

		~InputFileStream();

	public:
		ErrorCode Open(PathView filepath, FileFlags flags = FILEFLAGS_None);

		void Close();

		ErrorCode Read(SizeT file_offset, Vector<ByteT>& out_file_buffer);

		ErrorCode Read(SizeT file_offset, void* out_file_buffer, SizeT file_buffer_size, SizeT& out_written);

	private:
		void* m_NativeFileHandle;
		FileFlags m_FileFlags;
	};

} }