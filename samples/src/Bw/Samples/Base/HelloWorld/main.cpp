#include <iostream>
#include "Bw/Base/Module.h"

int main(int argc, char** argv)
{
	bw::init_base();

	std::cout << BW_BASE_VERSION_STRING << std::endl;

	bw::shutdown_base();

	return 0;
}