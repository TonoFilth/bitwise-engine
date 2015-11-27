#include <iostream>
#include <cstdio>
#include "Bw/Base/Module.h"

using namespace std;
using namespace bw;

int main(int argc, char** argv)
{
    init_base();

	cout << BW_BASE_VERSION_STRING << endl;

    

    //BW_ASSERT(1 == 2);

	shutdown_base();

	return 0;
}