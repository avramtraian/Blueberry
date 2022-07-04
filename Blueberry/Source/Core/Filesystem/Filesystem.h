// Copyright to Avram Traian. 2022 - 2022.
// File created on July 3 2022.

#pragma once

#include "FilesystemErrorCodes.h"
#include "Path.h"
#include "FileStream.h"

namespace Blueberry { namespace Filesystem {

	BLUEBERRY_API const Path& GetWorkingDirectory();

	BLUEBERRY_API void SetWorkingDirectory(PathView new_working_directory);

	BLUEBERRY_API ErrorCode FileDelete(PathView filepath);

	BLUEBERRY_API ErrorCode FileCopy(PathView src_filepath, PathView dest_filepath);

	BLUEBERRY_API ErrorCode FileMove(PathView src_filepath, PathView dest_filepath);

	BLUEBERRY_API ErrorCode FileRename(const Path& filepath, StringView new_filename);

	bool Initialize();

	void Shutdown();

} }