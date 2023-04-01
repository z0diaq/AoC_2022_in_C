#include <stdio.h>
#include <stdlib.h> //errno
#include <string.h> //strtok_s

#include "aoc.h"

struct Context
{
	size_t m_sumCalories;
	size_t m_partialSum;
};

void Process( const char* line, struct Context* ctx );

int
main( int _argc, char* _argv[ ] )
{
	char* fileContents = NULL;
	const char sep = '\n';
	size_t fileContentsSize = 0;

	if( false == ReadSampleData( "day01\\sample_input_a.txt", &fileContents, &fileContentsSize ) )
		return EXIT_FAILURE;

	int result = EXIT_SUCCESS;
	size_t pos = 0, from = 0;

	struct Context ctx = { 0, 0 };

	while( pos < fileContentsSize )
	{
		if( fileContents[ pos ] == sep || pos == ( fileContentsSize - 1 ) )
		{
			if( pos < ( fileContentsSize - 1 ) )
				fileContents[ pos ] = 0;

			Process( fileContents + from, &ctx );
			from = pos + 1;
		}
		++pos;
	}

	RELEASE( fileContents );

	LOG_INFO( "Result: [%zu]", ctx.m_sumCalories );

	return result;
}

void Process( const char* line, struct Context* ctx )
{

	LOG_INFO( "Line [%s]", line );

	if( strlen( line ) == 0 )
		ctx->m_partialSum = 0;
	else
	{
		ctx->m_partialSum += strtoull( line, NULL, 10 );
		ctx->m_sumCalories = max( ctx->m_sumCalories, ctx->m_partialSum );
	}
}
