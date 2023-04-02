#include <stdio.h>
#include <string.h> //strlen, strcmp

#include "aoc.h"

struct Context
{
	size_t sumCalories;
	size_t partialSum;
};

enum ComputeResult
{
	ComputeResultMatch,
	ComputeResultNoInput,
	ComputeResultNoResult,
	ComputeResultNoMatch
};

void Process( const char* _line, struct Context* _ctx );
enum ResultType Compute( const char* _relativePathWithFilestem, enum AccessType _access );
bool IsResultAcceptable( enum ComputeResult _result );

int
main( int _argc, char* _argv[ ] )
{
	bool ok = IsResultAcceptable( Compute( "day01/sample_input_a", Public ) );
	ok = ok && IsResultAcceptable( Compute( "day01/input", Private ) );

	const int result = ( ok ? 0 : 1 );

	if( result )
	{
		LOG_ERROR( "Final result is: [%d]", result );
	}
	else
	{
		LOG_INFO( "Final result is: [%d]", result );
	}

	return result;
}

enum ResultType
Compute( const char* _relativePathWithFilestem, enum AccessType _access )
{
	const char sep = '\n';

	struct TestData data = {
		.relativePathWithFilestem = _relativePathWithFilestem,
		.accessType = _access
	};

	if( false == ReadSampleData( &data ) )
		return ComputeResultNoInput;

	LOG_DEBUG( "Processing data..." );

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

	enum ResultType result = ComputeResultMatch;

	char szResult[ 32 ];
	snprintf(
		szResult,
		32,
		"%zu",
		ctx.sumCalories );

	if( data.expectedResult.isRead )
	{
		if( strcmp( data.expectedResult.data, szResult ) )
		{
			LOG_ERROR(
				"FAIL: expected result [%s] does not match computed [%s]",
				data.expectedResult.data,
				szResult );
			result = ComputeResultNoMatch;
		}
		else
		{
			LOG_INFO(
				"OK: computed result [%s] matches expected",
				szResult );
		}
	}
	else
	{
		LOG_DEBUG( "Result: [%s] (no data to compare against)", szResult );
		result = ComputeResultNoResult;
	}

	RELEASE( data.expectedResult.data );

	return result;
}

void
Process( const char* _line, struct Context* _ctx )
{
	LOG_DEBUG( "Line [%s]", _line );

	if( strlen( _line ) == 0 )
		_ctx->partialSum = 0;
	else
	{
		_ctx->partialSum += strtoull( _line, NULL, 10 );
		_ctx->sumCalories = max( _ctx->sumCalories, _ctx->partialSum );
	}
}

bool
IsResultAcceptable( enum ComputeResult _result )
{
	switch( _result )
	{
	case ComputeResultMatch:
	case ComputeResultNoResult:
		return true;
	default:
		return false;
	}
}
