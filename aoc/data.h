#pragma once

#include "utils.h"
#include "array.h"

#include <stdbool.h>
#include <stddef.h>

enum AccessType
{
	Private,
	Public
};

const char* AccessTypeToString( enum AccessType _access );

struct DataLocationInfo
{
	const char*     relativePathWithFilestem;// i.e. day01/sample_input_a
	enum AccessType accessType;// look for data in either public or private dirs
};

struct TestData
{
	struct Array* input;
	struct Array* expectedResultPart1;
	struct Array* expectedResultPart2;
};

struct TestData* ReadTestData( struct DataLocationInfo _dataLocation );
