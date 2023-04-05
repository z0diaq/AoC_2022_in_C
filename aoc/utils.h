#pragma once

#include <stdlib.h>

#define RELEASE(chunk) free(chunk);chunk = NULL

#ifdef NDEBUG
#define FLUSH(stream)
#else
#define FLUSH(stream) fflush(stream)
#endif

#define LOG(...)  do { fprintf(stdout, __VA_ARGS__ ); fprintf(stdout, "\n"); FLUSH( stdout ); } while( 0 )
#define LOG_ERROR(...) do { fprintf(stderr, "ERROR: " __VA_ARGS__ ); fprintf(stderr, "\n"); FLUSH( stderr ); } while( 0 )
#define LOG_INFO(...) do { fprintf(stdout, "INFO: " __VA_ARGS__ ); fprintf(stdout, "\n"); FLUSH( stdout ); } while( 0 )

#ifdef _DEBUG
#define LOG_DEBUG(...) do { fprintf(stdout, "DEBUG: " __VA_ARGS__ ); fprintf(stdout, "\n"); FLUSH( stdout ); } while( 0 )
#else
#define LOG_DEBUG(...)
#endif

// min and max macros are pure evil
size_t min_size_t( size_t _lhs, size_t _rhs );
size_t max_size_t( size_t _lhs, size_t _rhs );


#define STRINGIFY(_x) STRINGIFY2(_x)
#define STRINGIFY2(_x) #_x

#define VERIFY_IS_ZERO(_cmd)                                                           \
{                                                                                      \
	const int errorCode = ( _cmd );                                                    \
	if(errorCode)                                                                      \
	{                                                                                  \
		LOG_ERROR( "Command [%s] failed with error [%d]", STRINGIFY(_cmd), errorCode); \
		return false;                                                                  \
	}                                                                                  \
}

#define VERIFY_NOT_NULL(_cmd)                                                          \
{                                                                                      \
	if(NULL == ( _cmd ) )                                                              \
	{                                                                                  \
		LOG_ERROR( "Command [%s] failed with error [%d]", STRINGIFY(_cmd), errno);     \
		return false;                                                                  \
	}                                                                                  \
}

#define ASSURE(_var)                                                                   \
if( ! ( _var ) )                                                                       \
{                                                                                      \
	LOG_ERROR( STRINGIFY(_var) " failed - aborting operation!" );                      \
	exit( 1 );                                                                         \
}
