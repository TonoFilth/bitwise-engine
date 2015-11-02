#include <iostream>
#include <cstdio>
#include <Bw/Bw.h>

using namespace std;

void test_stack()
{
    char** buff = NULL;
    int nbFrames = bw::stack_trace(&buff);

    cout << "NbFrames: " << nbFrames << endl;
    cout << "Buff: " << buff << endl;

    for (int i = 0; i < nbFrames; ++i)
        cout << buff[i] << endl;    

    free(buff);
}

int main(int argc, char** argv)
{
	cout << "HelloWorld Sample" << endl;

	bw::Init();

    test_stack();
	
    bw::Shutdown();

	return 0;
}