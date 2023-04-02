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

enum AccessType
{
	Private,
	Public
};

struct TestData
{
	//in
	const char*         relativePathWithFilestem;// i.e. day01/sample_input_a
	enum AccessType     accessType; // look for data in either public or private dirs

	//out
	struct FileContents input;
	struct FileContents expectedResult;
};

bool ReadSampleData( struct TestData* data );
