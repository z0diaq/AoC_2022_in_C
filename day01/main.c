#include "runner.h"

struct ExecuteSetup PrepareSetupPart1( );
struct ExecuteSetup PrepareSetupPart2( );

int
main( int _argc, char* _argv[ ] )
{

	struct DataLocationInfo testsData[] = {
		{ "day01/sample_input_a", Public },
		{ "day01/input", Private },
		{ NULL, Public }
	};

	return Execute( testsData, PrepareSetupPart1( ), PrepareSetupPart2( ) );
}
