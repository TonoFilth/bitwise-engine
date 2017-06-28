#if !defined(BW_DOXYPRESS)
#pragma once

namespace bw
{
// -------------------------------------------------------------------------
//  Internal namespace
// -------------------------------------------------------------------------
namespace internal
{
namespace network
{
	// Defined in "bitwise/network.cpp"
    void initialize(int argc, char** argv);
    void shutdown();
}
}   // namespace internal
}   // namespace bw

#endif