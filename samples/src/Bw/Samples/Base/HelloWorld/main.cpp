#include <iostream>
#include "Bw/Base/Module.h"

int main(int argc, char** argv)
{
	bw::init_base();

	std::cout << BW_BASE_VERSION_STRING << std::endl;

    BW_ASSERT(1 == 2);

	bw::shutdown_base();

	return 0;
}