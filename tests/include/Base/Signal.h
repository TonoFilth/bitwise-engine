#include <csignal>
#include <Catch/Catch.hpp>
#include <Bw/Base/Signal.h>

using namespace bw;

static bool s_signalsHandled[Signal::eCOUNT];

////////////////////////////////////////////////////////////////////////////////
//  TestSignalHandler
////////////////////////////////////////////////////////////////////////////////
void TestSignalHandler(Signal::Enum signal)
{
	s_signalsHandled[signal] = true;
}

////////////////////////////////////////////////////////////////////////////////
//  Test Case
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Signal Handlers", "[base]")
{
	// Make sure no signals are handled before running the tests
	for (int i = 0; i < Signal::eCOUNT; ++i)
		s_signalsHandled[(Signal::Enum) i] = false;

	SECTION("Raise all signals")
	{
		// Register signal handler
		for (int i = 0; i < Signal::eCOUNT; ++i)
			SetSignalHandler((Signal::Enum) i, TestSignalHandler);

		// Raise all signals
		raise(SIGABRT);
		raise(SIGFPE);
		raise(SIGILL);
		raise(SIGINT);
		raise(SIGSEGV);
		raise(SIGTERM);

		// Check if all handlers were called
		for (int i = 0; i < Signal::eCOUNT; ++i)
			REQUIRE(s_signalsHandled[(Signal::Enum) i]);
	}
}