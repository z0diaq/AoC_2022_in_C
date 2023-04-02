#include "aoc.h"

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

bool ReadData( const char* _relativePathWithFilestem, const char* _postfix, struct FileContents* _contents );
void Init( struct FileContents* _contents );

bool
ReadSampleData( struct TestData* _data )
{
	Init( &_data->input );
	Init( &_data->expectedResult );

	if( false == ReadData(
		_data->relativePathWithFilestem,
		NULL,
		&_data->input ) )
	{
		return false;
	}

	ReadData(
		_data->relativePathWithFilestem,
		"_result",
		&_data->expectedResult );

	return true;
}

bool
ReadData( const char* _relativePathWithFilestem, const char* _postfix, struct FileContents* _contents )
{
	LOG_DEBUG( "_relativePathWithFilestem: [%s] _postfix: [%s]", _relativePathWithFilestem, _postfix );

	const size_t postfixLength = ( _postfix ? strlen( _postfix ) : 0 );

	if( strlen( DATA_ROOT_DIR ) + strlen( _relativePathWithFilestem ) + postfixLength + 5 >= MAX_PATH )
	{
		LOG_ERROR(
			"Data path [%s] or file path [%s] + postfix [%s] too long and combined exceeds [%d B] value",
			DATA_ROOT_DIR,
			_relativePathWithFilestem,
			_postfix,
			MAX_PATH );
		return false;
	}

	char fullPath[ MAX_PATH ] = { 0 };

	VERIFY_NOT_NULL( strcpy( fullPath, DATA_ROOT_DIR ) );
	VERIFY_NOT_NULL( strcat( fullPath, "\\" ) );
	VERIFY_NOT_NULL( strcat( fullPath, _relativePathWithFilestem ) );
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

	_contents->data = malloc( sizeFile + 1 );

	if( NULL == _contents->data )
	{
		LOG_ERROR( "Could not allocate [%zu B] for file contents", sizeFile + 1u );
		return false;
	}

	_contents->size = fread( _contents->data, sizeof( char ), sizeFile, file );

	if( fclose( file ) || ferror( file ) )
	{
		LOG_ERROR( "Error [%d] during data read from [%s]", errno, fullPath );
		RELEASE( _contents->data );
		return false;
	}

	LOG_DEBUG( "Read [%llu B]", _contents->size );
	_contents->data[ _contents->size ] = 0;
	_contents->isRead = true;

	return true;
}

void
Init( struct FileContents* _contents )
{
	_contents->isRead = false;
	_contents->data   = NULL;
	_contents->size   = 0;
}
