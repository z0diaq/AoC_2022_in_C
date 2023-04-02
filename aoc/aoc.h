#pragma once

#include "utils.h"

#include <stdbool.h>
#include <stddef.h>

struct FileContents
{
	bool   isRead;
	char*  data;
	size_t size;
};

struct TestData
{
	//in
	const char*         relativePathWithFilestem;// i.e. day01/sample_input_a
	bool                isPublic; // if true look in public dir, if false look in private (not in CVS) dir

	//out
	struct FileContents input;
	struct FileContents expectedResult;
};

bool ReadSampleData( struct TestData* data );
