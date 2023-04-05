#include "data.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifndef DATA_ROOT_DIR
#error DATA_ROOT_DIR must be provided!
#endif

#ifndef _MSC_VER
#include <linux/limits.h>
#define MAX_PATH PATH_MAX
#else
#define MAX_PATH _MAX_PATH
#endif

void
ExtractLines( struct Array* _lines, const char* _contents, const size_t _size );

bool
ReadFileContents( struct DataLocationInfo _dataLocation, const char* _postfix, struct Array* _lines );

struct TestData*
ReadTestData( struct DataLocationInfo _dataLocation )
{
	struct TestData* data = ( struct TestData* )calloc( 1, sizeof( struct TestData ) );

	if( !data )
		return data;

	data->input = ArrayCreate( 2, sizeof( char* ) );
	data->expectedResultPart1 = ArrayCreate( 2, sizeof( char* ) );
	data->expectedResultPart2 = ArrayCreate( 2, sizeof( char* ) );

	if( false == ReadFileContents(
		_dataLocation,
		NULL,
		data->input ) )
	{
		goto read_cleanup;
	}

	ReadFileContents(
		_dataLocation,
		"_result_part1",
		data->expectedResultPart1 );

	if( ArraySize( data->expectedResultPart1 ) > 1 )
	{
		LOG_ERROR(
			"Result must contain exactly one line but [%zu] was read - please verify file",
			ArraySize( data->expectedResultPart1 ) );
		goto read_cleanup;
	}

	ReadFileContents(
		_dataLocation,
		"_result_part2",
		data->expectedResultPart2 );

	if( ArraySize( data->expectedResultPart2 ) > 1 )
	{
		LOG_ERROR(
			"Result must contain exactly one line but [%zu] was read - please verify file",
			ArraySize( data->expectedResultPart2 ) );
		goto read_cleanup;
	}

	goto read_end;

read_cleanup:
	ArrayDestroy( &data->input );
	ArrayDestroy( &data->expectedResultPart1 );
	ArrayDestroy( &data->expectedResultPart2 );

	RELEASE( data );

read_end:

	return data;
}

bool
ReadFileContents( struct DataLocationInfo _dataLocation, const char* _postfix, struct Array* _lines )
{
	LOG_DEBUG( "_relativePathWithFilestem: [%s] _postfix: [%s]", _dataLocation.relativePathWithFilestem, _postfix );

	const size_t postfixLength = ( _postfix ? strlen( _postfix ) : 0 );
	const char* dataSubDir = ( _dataLocation.accessType == Public ? "data/public" : "data/private" );

	if( strlen( DATA_ROOT_DIR ) + strlen( dataSubDir ) + strlen( _dataLocation.relativePathWithFilestem ) + postfixLength + 5 >= MAX_PATH )
	{
		LOG_ERROR(
			"Data path [%s/%s] or file path [%s] + postfix [%s] too long and combined exceeds [%d B] value",
			DATA_ROOT_DIR,
			dataSubDir,
			_dataLocation.relativePathWithFilestem,
			_postfix,
			MAX_PATH );
		return false;
	}

	char fullPath[ MAX_PATH ] = { 0 };

	VERIFY_NOT_NULL( strcpy( fullPath, DATA_ROOT_DIR ) );
	VERIFY_NOT_NULL( strcat( fullPath, "/" ) );
	VERIFY_NOT_NULL( strcat( fullPath, dataSubDir ) );
	VERIFY_NOT_NULL( strcat( fullPath, "/" ) );
	VERIFY_NOT_NULL( strcat( fullPath, _dataLocation.relativePathWithFilestem ) );
	if( _postfix )
		VERIFY_NOT_NULL( strcat( fullPath, _postfix ) );
	VERIFY_NOT_NULL( strcat( fullPath, ".txt" ) );

	LOG_DEBUG( "Full path: [%s]", fullPath );

	FILE* file = fopen( fullPath, "r" );

	if( NULL == file )
	{
		LOG_ERROR( "Could not open [%s] - error: [%d]", fullPath, errno );
		return false;
	}

	VERIFY_IS_ZERO( fseek( file, 0, SEEK_END ) );

	const size_t sizeFile = ftell( file );

	LOG_DEBUG( "[%s] has size of [%llu B]", fullPath, sizeFile );

	VERIFY_IS_ZERO( fseek( file, 0, SEEK_SET ) );

	char* contents = malloc( sizeFile + 1 );

	if( NULL == contents )
	{
		LOG_ERROR( "Could not allocate [%zu B] for file contents", sizeFile + 1u );
		return false;
	}

	size_t size = fread( contents, sizeof( char ), sizeFile, file );

	if( fclose( file ) || ferror( file ) )
	{
		LOG_ERROR( "Error [%d] during data read from [%s]", errno, fullPath );
		RELEASE( contents );
		return false;
	}

	ExtractLines( _lines, contents, size );

	RELEASE( contents );

	LOG_DEBUG( "Read [%zu] lines from [%s]", ArraySize( _lines ), fullPath );

	return true;
}

void
ExtractLines( struct Array* _lines, const char* _contents, const size_t _size )
{
	const char sep = '\n';
	size_t pos = 0, from = 0;

	char* line;

	while( pos < _size )
	{
		if( _contents[ pos ] == sep || pos == ( _size - 1 ) )
		{
			size_t length = pos - from;

			//last byte might not be sep
			if( pos == ( _size - 1 ) && _contents[ pos ] != sep )
				++length;

			line = malloc( length + 1 );
			if( line )
			{
				memcpy( line, _contents + from, length * sizeof( char ) );
				line[ length ] = 0;

				ArrayPush( _lines, line );
			}

			from = pos + 1;
		}
		++pos;
	}
}

const char*
AccessTypeToString( enum AccessType _access )
{
	switch( _access )
	{
	case Private:
		return "Private";
	case Public:
		return "Public";
	}

	return NULL;
}
