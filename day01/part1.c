
#include "runner.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct ContextPart1
{
	size_t sumCalories;
	size_t partialSum;
};


void* CreateCtxPart1( )
{
	struct ContextPart1* result = ( struct ContextPart1* )malloc( sizeof( struct ContextPart1 ) );
	if( !result ) return NULL;

	result->partialSum = 0;
	result->sumCalories = 0;

	return result;
}

void PrepareResultPart1( char** _output, void* _ctx )
{
	struct ContextPart1* ctx = ( struct ContextPart1* )_ctx;

	*_output = ( char* )malloc( 32 * sizeof( char ) );
	snprintf( *_output, 32, "%zu", ctx->sumCalories );
}

void
ProcessPart1( const char* _line, struct ContextPart1* _ctx )
{
	if( strlen( _line ) == 0 )
		_ctx->partialSum = 0;
	else
	{
		_ctx->partialSum += strtoull( _line, NULL, 10 );
		_ctx->sumCalories = max_size_t( _ctx->sumCalories, _ctx->partialSum );
	}
}

struct ExecuteSetup
PrepareSetupPart1( )
{
	struct ExecuteSetup result =
	{
		.createCtx       = CreateCtxPart1,
		.destroyCtx      = NULL,
		.processFunction = ProcessPart1,
		.resultFunction  = PrepareResultPart1
	};

	return result;
}
