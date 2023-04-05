#pragma once

#include <stddef.h>

enum MatchResult
{
	MatchResultLost,
	MatchResultDraw,
	MatchResultWon
};

#define ROCK 'A'
#define PAPER 'B'
#define SCISSORS 'C'

struct Context
{
	size_t totalScore;
};

size_t ComputeScore( char _selecetedShape, enum MatchResult _matchResult );
void* CreateCtx( );
void PrepareResult( char** _output, void* _ctx );
