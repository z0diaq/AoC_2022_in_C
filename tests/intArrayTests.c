#include <stdio.h>
#include <stdbool.h>

#include "array.h"
#include "testHelpers.h"

DECLARE_TEST( canCreateAndDestroy );
DECLARE_TEST( keepsCapacity );
DECLARE_TEST( canPushOneValue );
DECLARE_TEST( canPushMultipleValues );
DECLARE_TEST( canPushAndRead10Values );

int intArrayTests( int ac, char* av[ ] )
{
	int testsResult = 0, testsPassed = 0, testsExecuted = 0;

	TEST_RESULT( canCreateAndDestroy( ) );
	TEST_RESULT( keepsCapacity( ) );
	TEST_RESULT( canPushOneValue( ) );
	TEST_RESULT( canPushMultipleValues( ) );
	TEST_RESULT( canPushAndRead10Values( ) );

	LOG_INFO( "Executed [%d] tests of which [%d] passed", testsExecuted, testsPassed );
	return testsResult;
}

TEST_BEGIN( canCreateAndDestroy )
	struct Array *intArray = ArrayCreate( 2, sizeof( int ) );
	CHECK_TRUE( 0 == ArraySize( intArray ) );
	CHECK_TRUE( ArrayCapacity( intArray ) == 2 );

	ArrayDestroy( &intArray );
	CHECK_TRUE( NULL == intArray );
TEST_END

TEST_BEGIN( keepsCapacity )
	struct Array* intArray = ArrayCreate( 10, sizeof( int ) );
	CHECK_TRUE( 0 == ArraySize( intArray ) );
	CHECK_TRUE( ArrayCapacity( intArray ) == 10 );

	ArrayDestroy( &intArray );
	CHECK_TRUE( NULL == intArray );
TEST_END

TEST_BEGIN( canPushOneValue )
	struct Array* intArray = ArrayCreate( 2, sizeof( int ) );

	int value = 1;
	ArrayPush( intArray, &value );
	CHECK_TRUE( 1 == ArraySize( intArray ) );
	CHECK_TRUE( ArrayCapacity( intArray ) == 2 );

	ArrayDestroy( &intArray );
TEST_END

TEST_BEGIN( canPushMultipleValues )
	struct Array* intArray = ArrayCreate( 2, sizeof( int ) );

	int value = 1;
	ArrayPush( intArray, &value );
	ArrayPush( intArray, &value );
	ArrayPush( intArray, &value );//resize!

	CHECK_TRUE( 3 == ArraySize( intArray ) );
	CHECK_TRUE( ArrayCapacity( intArray ) >= ArraySize( intArray ) );

	ArrayDestroy( &intArray );
TEST_END

TEST_BEGIN( canPushAndRead10Values )
	struct Array* intArray = ArrayCreate( 2, sizeof( int ) );

	for( int value = 0; value != 10; ++value )
		ArrayPush( intArray, &value );

	CHECK_TRUE( 10 == ArraySize( intArray ) );

	for( int value = 0; value != 10; ++value )
		CHECK_EQUAL_INT( value, *( int* )ArrayGet( intArray, value ) );

	ArrayDestroy( &intArray );
TEST_END