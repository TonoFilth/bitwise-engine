#include <AppKit/AppKit.h>
#include <Cocoa/Cocoa.h>
#include <csignal>
#include "Bw/Base/DefaultAssertHandler.h"
#include "Bw/Base/CharArray.h"
#include "Bw/Base/System.h"

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

    CharArray::Format(message, 512, "Expression: %s\nFile: %s:%d", exp, file, line);
    
    @autoreleasepool
    {
        NSAlert* alert = [[NSAlert alloc] init];
            [alert addButtonWithTitle:@"Abort"];
            [alert setMessageText:@"Assertion Failed!"];
            [alert setInformativeText:[NSString stringWithUTF8String:message]];
            [alert setAlertStyle:NSCriticalAlertStyle];
    
        if ([alert runModal] == NSAlertFirstButtonReturn)
        {
        }
        [alert release];
    }
    
    raise(SIGABRT);
}

}   // namespace bw