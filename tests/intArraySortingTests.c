#include <stdio.h>
#include <stdbool.h>

#include "array.h"
#include "testHelpers.h"

DECLARE_TEST( canSortTwoElements );
DECLARE_TEST( canSortTenElements );

int intArraySortingTests( int ac, char* av[ ] )
{
	int testsResult = 0, testsPassed = 0, testsExecuted = 0;

	TEST_RESULT( canSortTwoElements( ) );
	TEST_RESULT( canSortTenElements( ) );

	LOG_INFO( "Executed [%d] tests of which [%d] passed", testsExecuted, testsPassed );
	return testsResult;
}

TEST_BEGIN( canSortTwoElements )
	struct Array* intArray = ArrayCreate( 2, sizeof( int ) );
	int       values[ ] = { 20, 10 };
	int sortedValues[ ] = { 10, 20 };
	ArrayPush( intArray, &values[ 0 ] );
	ArrayPush( intArray, &values[ 1 ] );
	CHECK_TRUE( 2 == ArraySize( intArray ) );
	CHECK_TRUE( ArrayCapacity( intArray ) >= 2 );

	ArraySort( intArray );

	CHECK_EQUAL_INT( sortedValues[ 0 ], *(int *)ArrayGet( intArray, 0 ) );
	CHECK_EQUAL_INT( sortedValues[ 1 ], *(int *)ArrayGet( intArray, 1 ) );

	ArrayDestroy( &intArray );
	CHECK_TRUE( NULL == intArray );
TEST_END

TEST_BEGIN( canSortTenElements )
	struct Array* intArray = ArrayCreate( 2, sizeof( int ) );
	int       values[ ] = { 20, 10, 30, 80, 50, 90, 40, 60, 70,  0 };
	int sortedValues[ ] = {  0, 10, 20, 30, 40, 50, 60, 70, 80, 90 };

	for( size_t index = 0; index != 10; ++index )
		ArrayPush( intArray, &values[ index ] );

	CHECK_TRUE( 10 == ArraySize( intArray ) );
	CHECK_TRUE( ArrayCapacity( intArray ) >= 10 );

	ArraySort( intArray );


	for( size_t index = 0; index != 10; ++index )
		CHECK_EQUAL_INT( sortedValues[ index ], *( int* )ArrayGet( intArray, index ) );

	ArrayDestroy( &intArray );
	CHECK_TRUE( NULL == intArray );
TEST_END
