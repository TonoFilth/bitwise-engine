#ifndef BW_BASE_DEFAULT_ASSERT_HANDLER_H
#define BW_BASE_DEFAULT_ASSERT_HANDLER_H

#include <windows.h>
#include "Bw/Base/Common/ModuleTypes.h"
#include "Bw/Base/String.h"

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
	char message[512];

	bw::sprintf(message, 512, "Assertion failed: ( %s )\nFile: %s:%d", exp, file, line);
	MessageBox(nullptr, message, "Bitwise Engine - Assertion failed!", MB_OK | MB_ICONERROR);

	// Trigger a breakpoint and let the debugger take control
	// If no debugger is attached, stop the execution
	if (IsDebuggerPresent())
		DebugBreak();
	else
		FatalExit(0);
}

}	// namespace bw

#endif	// BW_BASE_DEFAULT_ASSERT_HANDLER_H