#include "Bw/Base/Common/AssertHandler.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Private variables
////////////////////////////////////////////////////////////////////////////////
static DefaultAssertHandler s_defaultAssertHandler;
static AssertHandler*       s_assertHandler = &s_defaultAssertHandler;

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

}	// namespace bw