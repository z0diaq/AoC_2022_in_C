#include "runner.h"
#include "shared.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

enum MatchResult
FindMatchResult( char _opponentChoice, char _myChoice )
{
	if( _opponentChoice == _myChoice )
		return MatchResultDraw;
	else if( _opponentChoice == ROCK )
	{
		if( _myChoice == PAPER )
			return MatchResultWon;
		else
			return MatchResultLost;
	}
	else if( _opponentChoice == PAPER )
	{
		if( _myChoice == SCISSORS )
			return MatchResultWon;
		else
			return MatchResultLost;
	}
	else // SCISSORS
	{
		if( _myChoice == ROCK )
			return MatchResultWon;
		else
			return MatchResultLost;
	}

	LOG_ERROR(
		"%s: Unhandled oponent choice [%c] and/or my value [%c]",
		__FUNCTION__,
		_opponentChoice,
		_myChoice );
	exit( 1 );

}

void
ProcessPart1( const char* _line, struct Context* _ctx )
{
	ASSURE( strlen( _line ) == 3 );

	char myResponse = 0;
	switch( _line[ 2 ] )
	{
	case 'X':
		myResponse = ROCK;
		break;
	case 'Y':
		myResponse = PAPER;
		break;
	case 'Z':
		myResponse = SCISSORS;
		break;
	}

	_ctx->totalScore += ComputeScore( myResponse, FindMatchResult( _line[ 0 ], myResponse ) );
}

struct ExecuteSetup
PrepareSetupPart1( )
{
	struct ExecuteSetup result =
	{
		.createCtx       = CreateCtx,
		.destroyCtx      = NULL,
		.processFunction = ProcessPart1,
		.resultFunction  = PrepareResult
	};

	return result;
}
