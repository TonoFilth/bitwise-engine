#include "Bw/Base/Assert.h"
#include "Bw/Base/DefaultAssertHandler.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Static variables
////////////////////////////////////////////////////////////////////////////////
static bw::DefaultAssertHandler s_DefaultAssertHandler;
static bw::AssertHandler*       s_CurrentAssertHandler = &s_DefaultAssertHandler;

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
AssertHandler& GetAssertHandler()
{
	return *s_CurrentAssertHandler;
}

// -----------------------------------------------------------------------------

AssertHandler& SetAssertHandler(AssertHandler* assertHandler)
{
	AssertHandler& prevHandler = *s_CurrentAssertHandler;

	// If 'assertHandler' var is nullptr we set the current
	// assert handler to the default one
	if (assertHandler == nullptr)
		s_CurrentAssertHandler = &s_DefaultAssertHandler;
	else
		s_CurrentAssertHandler = assertHandler;

	return prevHandler;
}

}	// namespace bw