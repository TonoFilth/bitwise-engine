#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>
#include "BwTests/Base/AllTests.h"

int main( int argc, char** argv )
{
	int result = Catch::Session().run( argc, argv );

	return result;
}