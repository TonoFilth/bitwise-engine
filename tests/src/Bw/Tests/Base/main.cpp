#define CATCH_CONFIG_RUNNER

#include <Catch/Catch.hpp>
#include "Bw/Tests/Base/AllTests.h"

int main(int argc, char** argv)
{
	int result = Catch::Session().run(argc, argv);

	return result;
}