#include "bitwise/core/assert.h"
#include "bitwise/core/internal.h"

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static bw::assert::AssertHandler m_handler = bw::internal::assert::default_handler;

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
assert::AssertHandler assert::get_handler()
{
    return m_handler;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
assert::AssertHandler assert::set_handler(AssertHandler assertHandler)
{
    AssertHandler prevHandler = m_handler;

    // If 'assertHandler' var is null we set the current
    // assert handler to the default one
    if (assertHandler == nullptr)
    {
        m_handler = bw::internal::assert::default_handler;
    }
    else
    {
        m_handler = assertHandler;
    }

    return prevHandler;
}

}   // namespace bw