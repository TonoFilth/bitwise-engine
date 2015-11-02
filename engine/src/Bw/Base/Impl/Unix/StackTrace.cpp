#include <execinfo.h>
#include "Bw/Base/Assert.h"
#include "Bw/Base/StackTrace.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
int stack_trace(char*** stackFrames)
{
    void* addresses[100];
    int nbAddresses = backtrace(addresses, 100);

    *stackFrames = backtrace_symbols(addresses, nbAddresses);

    return nbAddresses;
}

}   // namespace bw