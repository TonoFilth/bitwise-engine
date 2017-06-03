#include "bitwise/core/assert.h"
#include "bitwise/core/default_assert_handler.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static DefaultAssertHandler s_defaultAssertHandler;
static AssertHandler*       s_currentAssertHandler = &s_defaultAssertHandler;

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
AssertHandler& assert::get_handler()
{
    return *s_currentAssertHandler;
}

// -----------------------------------------------------------------------------

AssertHandler& assert::set_handler(AssertHandler* assertHandler)
{
    AssertHandler& prevHandler = *s_currentAssertHandler;

    // If 'assertHandler' var is null we set the current
    // assert handler to the default one
    if (assertHandler == nullptr)
    {
        s_currentAssertHandler = &s_defaultAssertHandler;
    }
    else
    {
        s_currentAssertHandler = assertHandler;
    }

    return prevHandler;
}

}   // namespace bw