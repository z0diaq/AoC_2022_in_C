#include "shared.h"

#include <stdio.h>
#include <stdlib.h>


size_t ComputeScore( char _selecetedShape, enum MatchResult _matchResult )
{
	size_t score = 0;

	switch( _selecetedShape )
	{
	case ROCK:
		score = 1;
		break;
	case PAPER:
		score = 2;
		break;
	case SCISSORS:
		score = 3;
		break;
	}

	switch( _matchResult )
	{
	case MatchResultLost:
		return score + 0;
	case MatchResultDraw:
		return score + 3;
	case MatchResultWon:
		return score + 6;
	}

	return 0;
}

void*
CreateCtx( )
{
	struct Context* result = ( struct Context* )malloc( sizeof( struct Context ) );
	if( !result ) return NULL;

	result->totalScore = 0;

	return result;
}

void
PrepareResult( char** _output, void* _ctx )
{
	struct Context* ctx = ( struct Context* )_ctx;

	*_output = ( char* )malloc( 32 * sizeof( char ) );
	snprintf( *_output, 32, "%zu", ctx->totalScore );
}
