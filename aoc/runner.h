#pragma once

#include "data.h"

typedef void* ( *CreateCtxFunction )( );
typedef void ( *DestroyCtxFunction )( void** ctx );
typedef void ( *ProcessFunction )( const char*, void* );
typedef void ( *ResultFunction )( char**, void* );

struct ExecuteSetup
{
	CreateCtxFunction  createCtx;
	DestroyCtxFunction destroyCtx;
	ProcessFunction    processFunction;
	ResultFunction     resultFunction;
};

int Execute(
	struct DataLocationInfo _dataLocations[],
	struct ExecuteSetup _setupPart1,
	struct ExecuteSetup _setupPart2 );

enum ComputeResult
{
	ComputeResultMatch,
	ComputeResultNoInput,
	ComputeResultNoResult,
	ComputeResultNoMatch
};
