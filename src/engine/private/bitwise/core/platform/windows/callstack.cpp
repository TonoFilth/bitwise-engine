#include <windows.h>
#include <winnt.h>

// Some versions of imagehlp.dll lack the proper packing directives themselves
// so we need to do it.
#pragma pack( push, before_imagehlp, 8 )
#pragma warning(push)
#pragma warning(disable : 4091)
#include <imagehlp.h>
#pragma warning(pop)
#pragma pack( pop, before_imagehlp )

#include "bitwise/core/cstring.h"
#include "bitwise/core/console.h"
#include "bitwise/core/callstack.h"

namespace bw
{

StackFrame* callstack::walk(int skip)
{
    // Set up the symbol options so that we can gather information from the current
    // executable's PDB files, as well as the Microsoft symbol servers.  We also want
    // to undecorate the symbol names we're returned.  If you want, you can add other
    // symbol servers or paths via a semi-colon separated list in SymInitialized.
    ::SymSetOptions( SYMOPT_DEFERRED_LOADS | SYMOPT_INCLUDE_32BIT_MODULES | SYMOPT_UNDNAME | SYMOPT_LOAD_LINES );
    if (!::SymInitialize( ::GetCurrentProcess(), "http://msdl.microsoft.com/download/symbols", TRUE )) return false;
 
    // Capture up to 25 stack frames from the current call stack.  We're going to
    // skip the first stack frame returned because that's the GetStackWalk function
    // itself, which we don't care about.
    PVOID addrs[ 25 ] = { 0 };
    USHORT frames = CaptureStackBackTrace( 1, 25, addrs, NULL );
 
    for (USHORT i = 0; i < frames; i++) {
        // Allocate a buffer large enough to hold the symbol information on the stack and get 
        // a pointer to the buffer.  We also have to set the size of the symbol structure itself
        // and the number of bytes reserved for the name.
        ULONG64 buffer[ (sizeof( SYMBOL_INFO ) + 1024 + sizeof( ULONG64 ) - 1) / sizeof( ULONG64 ) ] = { 0 };
        SYMBOL_INFO *info = (SYMBOL_INFO *)buffer;
        info->SizeOfStruct = sizeof( SYMBOL_INFO );
        info->MaxNameLen = 1024;
 
        StackFrame frame;

        // Attempt to get information about the symbol and add it to our output parameter.
        DWORD64 displacement = 0;
        if (::SymFromAddr( ::GetCurrentProcess(), (DWORD64)addrs[ i ], &displacement, info )) {
            
            cstring::copy(frame.function, StackFrame::MAX_FUNCTION_NAME, info->Name);
        }

        DWORD64  dwAddress;
        DWORD  dwDisplacement;
        IMAGEHLP_LINE64 line;

        line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
        dwAddress = (DWORD64) addrs[i]; // Address you want to check on.

        if (SymGetLineFromAddr64(::GetCurrentProcess(), dwAddress, &dwDisplacement, &line))
        {
            // SymGetLineFromAddr64 returned success
            cstring::copy(frame.filename, StackFrame::MAX_FILE_NAME, line.FileName);
            frame.line = line.LineNumber;
        }
        else
        {
            // SymGetLineFromAddr64 failed
            //DWORD error = GetLastError();
            //_tprintf(TEXT("SymGetLineFromAddr64 returned error : %d\n"), error);
        }

        console::write_format("#%d | %s %s:%d\n", i, frame.function, frame.filename, frame.line);
    }
 
    ::SymCleanup( ::GetCurrentProcess() );
 
    return nullptr;
}

// -----------------------------------------------------------------------------

void callstack::print(StackFrame* frame)
{
}

}   // namespace bw