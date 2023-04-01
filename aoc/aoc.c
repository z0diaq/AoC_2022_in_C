#include "aoc.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifndef DATA_ROOT_DIR
	#error DATA_ROOT_DIR must be provided!
#endif

#define PATH_LENGTH 128

#define STRINGIFY(x) STRINGIFY2(x)
#define STRINGIFY2(x) #x

#define VERIFY_IS_ZERO(cmd)                                                            \
{                                                                                      \
	const int errorCode = cmd;                                                         \
	if(errorCode)                                                                      \
	{                                                                                  \
		LOG_ERROR( "Command [%s] failed with error [%d]", STRINGIFY(cmd), errorCode);  \
		return false;                                                                  \
	}                                                                                  \
}

#define VERIFY_NOT_NULL(cmd)                                                           \
{                                                                                      \
	if(NULL == cmd)                                                                    \
	{                                                                                  \
		LOG_ERROR( "Command [%s] failed with error [%d]", STRINGIFY(cmd), errno);      \
		return false;                                                                  \
	}                                                                                  \
}

#ifndef _MSC_VER
	#include <linux/limits.h>
	#define MAX_PATH PATH_MAX
#else
	#define MAX_PATH _MAX_PATH
#endif


bool
ReadSampleData( const char* _path, char** _lines, size_t* length )
{
	FILE* file;

	char fullPath[ MAX_PATH ] = { 0 };

	if( strlen( DATA_ROOT_DIR ) + strlen( _path ) + 2 >= MAX_PATH )
	{
		LOG_ERROR( "Data path [%s] or file path [%s] too long and combined exceeds [%d B] value", DATA_ROOT_DIR, _path, MAX_PATH );
		return false;
	}

	VERIFY_NOT_NULL( strcpy( fullPath, DATA_ROOT_DIR ) );
	VERIFY_NOT_NULL( strcat( fullPath, "\\" ) );
	VERIFY_NOT_NULL( strcat( fullPath, _path ) );

	LOG_INFO( "Full path: [%s]", fullPath );

	file = fopen( fullPath, "r" );

	if( NULL == file )
	{
		LOG_ERROR( "Could not open [%s] - error: [%d]", fullPath, errno );
		return false;
	}

	VERIFY_IS_ZERO( fseek( file, 0, SEEK_END ) );

	const size_t sizeFile = ftell( file );

	LOG_DEBUG( "[%s] has size of [%llu B]", fullPath, sizeFile );

	VERIFY_IS_ZERO( fseek( file, 0, SEEK_SET ) );

	*_lines = malloc( sizeFile + 1 );

	if( NULL == *_lines )
	{
		LOG_ERROR( "Could not allocate [%llu B] for file contents", sizeFile + 1 );
		return false;
	}

	*length = fread( *_lines, sizeof( char ), sizeFile, file );

	VERIFY_IS_ZERO( fclose( file ) );

	if( ferror( file ) )
	{
		LOG_ERROR( "Error [%d] during data read from [%s]", errno, _path );
		free( *_lines );
		*_lines = NULL;
		return false;
	}

	LOG_DEBUG( "Read [%llu B]", *length );
	( *_lines )[ *length ] = 0;

	return true;
}
