#include "Bw/Base/Common/Assert.h"
#include "Bw/Base/Detail/DefaultAssertHandler.h"

namespace
{

////////////////////////////////////////////////////////////////////////////////
//  Private variables
////////////////////////////////////////////////////////////////////////////////
bw::DefaultAssertHandler s_DefaultAssertHandler;
bw::AssertHandler*       s_CurrentAssertHandler = &s_DefaultAssertHandler;

}   // private namespace

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
AssertHandler& bw::GetAssertHandler()
{
	return *s_CurrentAssertHandler;
}

// -----------------------------------------------------------------------------

AssertHandler& bw::SetAssertHandler(AssertHandler* assertHandler)
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