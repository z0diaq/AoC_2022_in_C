#include <stdio.h>
#include <stdlib.h> //errno
#include <string.h> //strtok_s

#include "aoc.h"

struct Context
{
	size_t m_sumCalories;
	size_t m_partialSum;
};

void Process( const char* _line, struct Context* _ctx );

int
main( int _argc, char* _argv[ ] )
{
	const char sep = '\n';

	struct TestData data = {
		.relativePathWithFilestem = "day01\\sample_input_a",
		.isPublic = true
	};

	LOG_DEBUG( "file: [%s]", data.relativePathWithFilestem );

	if( false == ReadSampleData( &data ) )
		return EXIT_FAILURE;

	LOG_DEBUG( "Processing data..." );

	int result = EXIT_SUCCESS;
	size_t pos = 0, from = 0;

	struct Context ctx = { 0, 0 };

	while( pos < data.input.size )
	{
		if( data.input.data[ pos ] == sep || pos == ( data.input.size - 1 ) )
		{
			if( pos < ( data.input.size - 1 ) )
				data.input.data[ pos ] = 0;

			Process( data.input.data + from, &ctx );
			from = pos + 1;
		}
		++pos;
	}

	RELEASE( data.input.data );

	bool resultMatch = true;

	if( data.expectedResult.isRead )
	{
		char szResult[ 32 ];
		snprintf(
			szResult,
			32,
			"%zu",
			ctx.m_sumCalories );

		LOG_DEBUG(
			"Expected result: [%s] vs computed result: [%s]",
			data.expectedResult.data,
			szResult );

		resultMatch = ( 0 == strcmp( data.expectedResult.data, szResult ) );
	}
	else
		LOG_DEBUG( "No expected result file found to compare our result against" );

	RELEASE( data.expectedResult.data );

	LOG_INFO(
		"Result: [%s]",
		resultMatch ? "passed" : "failed" );

	return resultMatch ? 0 : 1;
}

void Process( const char* _line, struct Context* _ctx )
{
	LOG_DEBUG( "Line [%s]", _line );

	if( strlen( _line ) == 0 )
		_ctx->m_partialSum = 0;
	else
	{
		_ctx->m_partialSum += strtoull( _line, NULL, 10 );
		_ctx->m_sumCalories = max( _ctx->m_sumCalories, _ctx->m_partialSum );
	}
}
