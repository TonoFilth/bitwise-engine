#include "Bw/Base/Common/AssertHandler.h"
#include "Bw/Base/_detail/DefaultAssertHandler.h"

namespace
{

////////////////////////////////////////////////////////////////////////////////
//  Private variables
////////////////////////////////////////////////////////////////////////////////
bw::DefaultAssertHandler s_defaultAssertHandler;
bw::AssertHandler*       s_assertHandler = &s_defaultAssertHandler;

}   // private namespace

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
AssertHandler& assert_handler::get()
{
	return *s_assertHandler;
}

// -----------------------------------------------------------------------------

AssertHandler& assert_handler::set(AssertHandler& assertHandler)
{
	AssertHandler& prevHandler = *s_assertHandler;
	s_assertHandler = &assertHandler;

	return prevHandler;
}

// -----------------------------------------------------------------------------

AssertHandler& assert_handler::reset_default()
{
    return assert_handler::set(s_defaultAssertHandler);
}

}	// namespace bw