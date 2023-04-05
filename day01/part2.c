#include "array.h"
#include "runner.h"

#include <stddef.h>//size_t etc
#include <stdio.h> //io
#include <stdlib.h>//qsort
#include <string.h>

struct ContextPart2
{
	struct Array* eachElfTotalCallories;
};

void*
CreateCtxPart2( )
{
	struct ContextPart2* result = ( struct ContextPart2* )malloc( sizeof( struct ContextPart2 ) );
	if( result )
	{
		result->eachElfTotalCallories = ArrayCreate( 2, sizeof( size_t ) );

		//prepare first element for further computation
		size_t zero = 0;
		ArrayPush( result->eachElfTotalCallories, &zero );
	}

	return result;
}

void
DestroyCtxPart2( void** _ctx )
{
	struct ContextPart2* ctx = *( struct ContextPart2** )_ctx;
	ArrayDestroy( &ctx->eachElfTotalCallories );
	RELEASE( ctx );
	*_ctx = NULL;
}

void
PrepareResultPart2( char** _output, struct ContextPart2* _ctx )
{
	struct ContextPart2* ctx = ( struct ContextPart2* )_ctx;

	const size_t size = ArraySize( _ctx->eachElfTotalCallories );
	ASSURE( size >= 3 );

	*_output = ( char* )malloc( 32 * sizeof( char ) );

	ArraySort( _ctx->eachElfTotalCallories );

	size_t totalCaloriesFromThreeTopElves = 0;
	for( size_t no = size - 3; no != size; ++no )
		totalCaloriesFromThreeTopElves += *( size_t* )ArrayGet( _ctx->eachElfTotalCallories, no );

	snprintf( *_output, 32, "%zu", totalCaloriesFromThreeTopElves );
}

void
ProcessPart2( const char* _line, struct ContextPart2* _ctx )
{
	if( strlen( _line ) == 0 )
	{
		size_t zero = 0;
		ArrayPush( _ctx->eachElfTotalCallories, &zero );
	}
	else
	{
		const size_t size = ArraySize( _ctx->eachElfTotalCallories );
		size_t* partialSum = ( size_t* )ArrayGet( _ctx->eachElfTotalCallories, size - 1 );
		*partialSum += strtoull( _line, NULL, 10 );
	}
}

struct ExecuteSetup
PrepareSetupPart2( )
{
	struct ExecuteSetup result =
	{
		.createCtx       = CreateCtxPart2,
		.destroyCtx      = DestroyCtxPart2,
		.processFunction = ProcessPart2,
		.resultFunction  = PrepareResultPart2
	};

	return result;
}
