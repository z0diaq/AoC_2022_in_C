#include "runner.h"
#include "shared.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

char
PrepareResponse( char _oponentChoice, enum MatchResult _expectedResult )
{
	if( _expectedResult == MatchResultLost )
	{
		switch( _oponentChoice )
		{
		case ROCK:
			return SCISSORS;
		case PAPER:
			return ROCK;
		case SCISSORS:
			return PAPER;
		}
	}

	if( _expectedResult == MatchResultDraw )
		return _oponentChoice;

	if( _expectedResult == MatchResultWon )
	{
		switch( _oponentChoice )
		{
		case ROCK:
			return PAPER;
		case PAPER:
			return SCISSORS;
		case SCISSORS:
			return ROCK;
		}
	}

	LOG_ERROR(
		"%s: Unhandled choice [%c] and/or expected result [%d]",
		__FUNCTION__,
		_oponentChoice,
		_expectedResult );
	exit( 1 );
}

enum MatchResult
MatchResultFromChar( char _myResponse )
{
	switch( _myResponse )
	{
	case 'X':
		return MatchResultLost;
	case 'Y':
		return MatchResultDraw;
	case 'Z':
		return MatchResultWon;
	}

	LOG_ERROR(
		"%s: Unhandled value [%c]",
		__FUNCTION__,
		_myResponse );
	exit( 1 );
}

void
ProcessPart2( const char* _line, struct Context* _ctx )
{
	ASSURE( strlen( _line ) == 3 );

	enum MatchResult matchResult = MatchResultFromChar( _line[ 2 ] );
	_ctx->totalScore += ComputeScore( PrepareResponse( _line[ 0 ], matchResult ), matchResult );
}

struct ExecuteSetup
PrepareSetupPart2( )
{
	struct ExecuteSetup result =
	{
		.createCtx = CreateCtx,
		.destroyCtx = NULL,
		.processFunction = ProcessPart2,
		.resultFunction = PrepareResult
	};

	return result;
}
