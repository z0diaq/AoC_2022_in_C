#include "aoc.h"

//#ifndef _POSIX
//#define _CRT_SECURE_NO_WARNINGS
//#endif

#include <stdio.h>
#include <stdlib.h> //errno
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
		LOG_ERROR( "Command [%hs] failed with error [%d]", STRINGIFY(cmd), errorCode); \
		return false;                                                                  \
	}                                                                                  \
}

#define VERIFY_NOT_NULL(cmd)                                                           \
{                                                                                      \
	if(NULL == cmd)                                                                    \
	{                                                                                  \
		LOG_ERROR( "Command [%hs] failed with error [%d]", STRINGIFY(cmd), errno);     \
		return false;                                                                  \
	}                                                                                  \
}


bool
ReadSampleData( const char* _path, char** _lines, size_t* length )
{
	FILE* file;

	char fullPath[ _MAX_PATH ] = { 0 };

	if( strlen( DATA_ROOT_DIR ) + strlen( _path ) + 2 >= _MAX_PATH )
	{
		LOG_ERROR( "Data path [%hs] or file path [%hs] too long and combined exceeds [%d B] value", DATA_ROOT_DIR, _path, _MAX_PATH );
		return false;
	}

	VERIFY_NOT_NULL( strcpy( fullPath, DATA_ROOT_DIR ) );
	VERIFY_NOT_NULL( strcat( fullPath, "\\" ) );
	VERIFY_NOT_NULL( strcat( fullPath, _path ) );

	LOG_INFO( "Full path: [%hs]", fullPath );

	file = fopen( fullPath, "r" );

	if( NULL == file )
	{
		LOG_ERROR( "Could not open [%hs] - error: [%d]", fullPath, errno );
		return false;
	}

	VERIFY_IS_ZERO( fseek( file, 0, SEEK_END ) );

	const size_t sizeFile = ftell( file );

	LOG_DEBUG( "[%hs] has size of [%llu B]", fullPath, sizeFile );

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
		LOG_ERROR( "Error [%d] during data read from [%hs]", errno, _path );
		free( *_lines );
		*_lines = NULL;
		return false;
	}

	LOG_DEBUG( "Read [%llu B]", *length );
	( *_lines )[ *length ] = 0;

	return true;
}
