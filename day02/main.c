#include "runner.h"

struct ExecuteSetup PrepareSetupPart1( );
struct ExecuteSetup PrepareSetupPart2( );

int
main( int _argc, char* _argv[ ] )
{

	struct DataLocationInfo testsData[] = {
		{ "day02/sample_input_a", Public },
		{ "day02/input", Private },
		{ NULL, Public }
	};

	return Execute( testsData, PrepareSetupPart1( ), PrepareSetupPart2( ) );
}
