#include <Windows.h>
#include <iostream>
#include <Bw/Bw.h>

void EntryPoint(void* userData)
{
}

struct Test
{
	Test(int n) : a(n) {}

	int a;
};

int main(int argc, char** argv)
{
	bw::Init();

	bw::Mutex  mutex;
	bw::Thread thread(EntryPoint);

	mutex.lock();

	bw::PImpl<4, 4> impl1;
	bw::PImpl<4, 4> impl2;

	impl1.create<Test>(25);
	impl2.copy<Test>(impl1);

	Test* t1 = (Test*) impl1;
	Test* t2 = (Test*) impl2;

	impl1.destroy<Test>();
	impl2.destroy<Test>();

	bw::Quit();

	return 0;
}