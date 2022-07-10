// Copyright to Avram Traian. 2022 - 2022.
// File created on July 3 2022.

#pragma once

#include "Core/CoreMinimal.h"

namespace Blueberry { namespace Filesystem {

	using ErrorCode = uint32_t;

	// Success.
	#define FILESYSTEM_ERROR_NONE                (0x00u)

	// Unknown.
	#define FILESYSTEM_ERROR_UNKNOWN             (0x01u)

	// File not found.
	#define FILESYSTEM_ERROR_FILE_NOT_FOUND      (0x02u)

	// File already exists.
	#define FILESYSTEM_ERROR_FILE_ALREADY_EXISTS (0x03u)

	// File is currently used in another process.
	#define FILESYSTEM_ERROR_FILE_IN_USE         (0x04u)

	// The specified buffer is too small.
	#define FILESYSTEM_ERROR_BUFFER_OVERFLOW     (0x05u)

	// The file handle wasn't created/initialized.
	#define FILESYSTEM_ERROR_INVALID_HANDLE		 (0x06u)

	// The data provided is invalid (incorrect or corrupted).
	#define FILESYSTEM_ERROR_INVALID_DATA        (0x07u)

} }