#include "runner.h"
#include "array.h"

#include <stdio.h>
#include <string.h>

enum ComputeResult
Solve( struct Array* _input, struct Array* _expectedResult, struct ExecuteSetup* _setup );

bool
IsResultAcceptable( enum ComputeResult _result );

int
Execute( struct DataLocationInfo _dataLocations[ ],
	struct ExecuteSetup _setupPart1,
	struct ExecuteSetup _setupPart2 )
{
	LOG_DEBUG( "Preparing data..." );
	struct Array* dataArray = ArrayCreate( 2, sizeof( struct TestData* ) );

	struct DataLocationInfo* dataLocation = _dataLocations;
	while( dataLocation->relativePathWithFilestem )
	{
		LOG_DEBUG(
			"Reading data from path [%s] location: [%s]",
			dataLocation->relativePathWithFilestem,
			AccessTypeToString( dataLocation->accessType ) );

		struct TestData* data = ReadTestData( *dataLocation );
		if( data )
			ArrayPush( dataArray, &data );

		++dataLocation;
	}

	const size_t dataCount = ArraySize( dataArray );
	if( 0 == dataCount )
	{
		LOG_ERROR( "No data could be read!" );
		return 1;
	}

	int result = 0;

	for( size_t dataNo = 0; dataNo != dataCount && 0 == result; ++dataNo )
	{
		LOG_INFO( "Using [%zu] data set...", dataNo );
		struct TestData* data = *( struct TestData** )ArrayGet( dataArray, dataNo );

		LOG_INFO( "Solving part 1..."  );
		if( false == IsResultAcceptable( Solve( data->input, data->expectedResultPart1, &_setupPart1 ) ) )
			result = 1;

		if( 0 == result )
		{
			LOG_INFO( "Solving part 2..." );

			if( false == IsResultAcceptable( Solve( data->input, data->expectedResultPart2, &_setupPart2 ) ) )
				result = 1;
		}
	}

	LOG_DEBUG( "Releasing memory..." );
	for( size_t dataNo = 0; dataNo != dataCount && 0 == result; ++dataNo )
	{
		struct TestData* data = *( struct TestData** )ArrayGet( dataArray, dataNo );

		ArrayDestroy( &data->input );
		ArrayDestroy( &data->expectedResultPart1 );
		ArrayDestroy( &data->expectedResultPart2 );

		RELEASE( data );
	}
	LOG_DEBUG( "Release sub data, time for top level array" );

	ArrayDestroy( &dataArray );
	LOG_DEBUG( "Memory released, all done!" );

	return result;
}

enum ComputeResult
Solve( struct Array* _lines, struct Array* _expectedResult, struct ExecuteSetup* _setup )
{
	LOG_DEBUG( "Processing data..." );

	void* ctx = ( *_setup->createCtx )( );

	if( !ctx )
	{
		LOG_INFO( "No context returned - assuming this part is not ready yet" );
		return ComputeResultNoResult;
	}

	const size_t linesToProcess = ArraySize( _lines );
	for( size_t lineNo = 0; lineNo != linesToProcess; ++lineNo )
		( *_setup->processFunction )( ArrayGet( _lines, lineNo ), ctx );

	enum ComputeResult result = ComputeResultMatch;

	char* szResult;
	( *_setup->resultFunction )( &szResult, ctx );

	if( ArraySize( _expectedResult ) == 1 )
	{
		if( strcmp( ( char* )ArrayGet( _expectedResult, 0 ), szResult ) )
		{
			LOG_ERROR(
				"FAIL: expected result [%s] does not match computed [%s]",
				( char* )ArrayGet( _expectedResult, 0 ),
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
		LOG_INFO( "Result: [%s] (no data to compare against)", szResult );
		result = ComputeResultNoResult;
	}

	RELEASE( szResult );

	if( _setup->destroyCtx )
		( *_setup->destroyCtx )( &ctx );

	RELEASE( ctx );

	return result;
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
