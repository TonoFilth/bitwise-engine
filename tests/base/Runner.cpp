#define CATCH_CONFIG_RUNNER

#include <Catch/Catch.hpp>
#include "AllTests.h"

int main(int argc, char** argv)
{
	int result = Catch::Session().run(argc, argv);

	return result;
}