#ifndef BW_BASE_DEFAULT_ASSERT_HANDLER_H
#define BW_BASE_DEFAULT_ASSERT_HANDLER_H

#include "Bw/Base/Common/ModuleTypes.h"
#include "SystemHeaders.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Class std functions
////////////////////////////////////////////////////////////////////////////////
DefaultAssertHandler::DefaultAssertHandler()
{
}

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void DefaultAssertHandler::operator()(const char* exp, const char* file, int line)
{
	// Trigger a breakpoint and let the debugger take control
	// If no debugger is attached, stop the execution
	if (IsDebuggerPresent())
		DebugBreak();
	else
		FatalExit(0);
}

}	// namespace bw

#endif	// BW_BASE_DEFAULT_ASSERT_HANDLER_H