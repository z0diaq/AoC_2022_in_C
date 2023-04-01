#include "aoc.h"

#include <stdio.h>
#include <stdlib.h> //errno
#include <string.h>

#ifndef DATA_ROOT_DIR
	#error DATA_ROOT_DIR must be provided!
#endif

#define PATH_LENGTH 128

#define STRINGIFY(x) STRINGIFY2(x)
#define STRINGIFY2(x) #x

#define VERIFY(cmd)                                                                    \
{                                                                                      \
	const errno_t errorCode = cmd;                                                     \
	if(errorCode)                                                                      \
	{                                                                                  \
		LOG_ERROR( "Command [%hs] failed with error [%d]", STRINGIFY(cmd), errorCode); \
		return false;                                                                  \
	}                                                                                  \
}

bool
ReadSampleData( const char* _path, char** _lines, size_t* length )
{
	FILE* file;

	char fullPath[ PATH_LENGTH ] = { 0 };
	VERIFY( strcpy_s( fullPath, PATH_LENGTH, DATA_ROOT_DIR ) );
	VERIFY( strcat_s( fullPath, PATH_LENGTH, "\\" ) );
	VERIFY( strcat_s( fullPath, PATH_LENGTH, _path ) );

	LOG_INFO( "Full path: [%hs]", fullPath );

	VERIFY( fopen_s( &file, fullPath, "r" ) );
	VERIFY( fseek( file, 0, SEEK_END ) );

	const size_t sizeFile = ftell( file );

	LOG_DEBUG( "[%hs] has size of [%llu B]", fullPath, sizeFile );

	VERIFY( fseek( file, 0, SEEK_SET ) );

	*_lines = malloc( sizeFile + 1 );

	if( NULL == *_lines )
	{
		LOG_ERROR( "Could not allocate [%llu B] for file contents", sizeFile + 1 );
		return false;
	}

	*length = fread( *_lines, sizeof( char ), sizeFile, file );

	VERIFY( fclose( file ) );

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
