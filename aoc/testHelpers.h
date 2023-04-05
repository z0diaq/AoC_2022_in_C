#pragma once

#include "utils.h"


#define CHECK_TRUE(_cmd)                                                                   \
if(!(_cmd))                                                                                \
{                                                                                          \
	LOG_ERROR( "Check [%s] failed", STRINGIFY(_cmd) );                                     \
	result = false;                                                                        \
}                                                                                          \

#define ENSURE_TRUE(_cmd)                                                                  \
if( !(_cmd) )                                                                              \
{                                                                                          \
	LOG_ERROR( "Critical check [%s] failed - aborting further tests!", STRINGIFY( _cmd ) );\
	return false;                                                                          \
}

#define CHECK_EQUAL_INT(_lhs, _rhs)                                                        \
{                                                                                          \
	int lhs = (_lhs);                                                                      \
	int rhs = (_rhs);                                                                      \
	if(lhs != rhs)                                                                         \
	{                                                                                      \
		LOG_ERROR( "Equality check failed - lhs: [%d] rhs: [%d]", lhs, rhs );              \
		result = false;                                                                    \
	}                                                                                      \
}

#define CHECK_RELEASED(_data)                                                              \
if( _data )                                                                                \
{                                                                                          \
	LOG_ERROR( "[%s] should be released at this point!", STRINGIFY( _data ) );             \
	result = false;                                                                        \
}

#define TEST_RESULT(_function)                                                             \
LOG_INFO( "Starting %s...", STRINGIFY( _function ) );                                      \
++testsExecuted;                                                                           \
if( false == ( _function ) )                                                               \
{                                                                                          \
	LOG_ERROR( "Test failed" );                                                            \
	testsResult = 1;                                                                       \
}                                                                                          \
else                                                                                       \
{                                                                                          \
	++testsPassed;                                                                         \
	LOG_INFO( "Test passed" );                                                             \
}

#define DECLARE_TEST(_name) static bool _name( )

#define TEST_BEGIN(_name) bool _name( )                                                    \
{                                                                                          \
	bool result = true;

#define TEST_END return result; }
