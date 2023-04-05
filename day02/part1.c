
#include "runner.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct ContextPart1
{
	size_t totalScore;
};

enum MatchResult
{
	MatchResultLost,
	MatchResultDraw,
	MatchResultWon
};

static char Rock = 'A';
static char Paper = 'B';
static char Scissors = 'C';

size_t ComputeScore( char _selecetedShape, enum MatchResult _matchResult )
{
	size_t score = 0;

	switch( _selecetedShape )
	{
	case 'A':
		score = 1;
		break;
	case 'B':
		score = 2;
		break;
	case 'C':
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
}

enum MatchResult
	FindMatchResult( char _opponentChoice, char _myChoice )
{
	if( _opponentChoice == _myChoice )
		return MatchResultDraw;
	else if( _opponentChoice == Rock )
	{
		if( _myChoice == Paper )
			return MatchResultWon;
		else
			return MatchResultLost;
	}
	else if( _opponentChoice == Paper ) 
	{
		if( _myChoice == Scissors )
			return MatchResultWon;
		else
			return MatchResultLost;
	}
	else // Scissors
	{
		if( _myChoice == Rock )
			return MatchResultWon;
		else
			return MatchResultLost;
	}
}

void* CreateCtxPart1( )
{
	struct ContextPart1* result = ( struct ContextPart1* )malloc( sizeof( struct ContextPart1 ) );
	if( !result ) return NULL;

	result->totalScore = 0;

	return result;
}

void PrepareResultPart1( char** _output, void* _ctx )
{
	struct ContextPart1* ctx = ( struct ContextPart1* )_ctx;

	*_output = ( char* )malloc( 32 * sizeof( char ) );
	snprintf( *_output, 32, "%zu", ctx->totalScore );
}

void
ProcessPart1( const char* _line, struct ContextPart1* _ctx )
{
	char myResponse = 0;
	switch( _line[ 2 ] )
	{
	case 'X':
		myResponse = Rock;
		break;
	case 'Y':
		myResponse = Paper;
		break;
	case 'Z':
		myResponse = Scissors;
		break;
	}

	_ctx->totalScore += ComputeScore( myResponse, FindMatchResult( _line[ 0 ], myResponse ) );
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
