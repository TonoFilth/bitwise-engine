#define CATCH_CONFIG_RUNNER
#include <Catch/Catch.hpp>
#include <Bw/Base/Module.h>
#include "Base/AllTests.h"

int main( int argc, char** argv )
{
	bw::InitBase();

	int result = Catch::Session().run( argc, argv );

	bw::ShutdownBase();

	return result;
}