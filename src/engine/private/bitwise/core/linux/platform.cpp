#include <cstdlib>
#include <unistd.h>
#include <backtrace.h>
#include <cxxabi.h>
#include "bitwise/core/platform.h"
#include "bitwise/core/cstring.h"
#include "bitwise/core/backtrace.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const size_t MAX_CMD_LENGTH   = 1024;
static const size_t MAX_STACK_FRAMES = 256;

// -----------------------------------------------------------------------------
//  Private types
// -----------------------------------------------------------------------------
struct BacktraceData
{
    StackFrame* currentFrame = nullptr;
    int frameNumber = 0;
};

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static StackFrame m_stackFrames[MAX_STACK_FRAMES];

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------
ssize_t get_executable_path(char* buffer, size_t size)
{
    size_t nbChars = readlink("/proc/self/exe", buffer, size);
    buffer[nbChars] = '\0';
    return nbChars;
}

// -----------------------------------------------------------------------------

int full_backtrace_callback(void* data, uintptr_t pc, const char* filename, int line, const char* function)
{
    int status;
    char* realname;


    realname = abi::__cxa_demangle(function, 0, 0, &status);

    const char* fn   = realname;
    const char* file = filename;

    if (filename == nullptr)
    {
        file = "???";
    }
    else
    {
        file = filename;
    }

    if (realname == nullptr)
    {
        if (function == nullptr)
        {
          fn = "???";
        }
        else
        {
          fn = function;
        }
    }

    BacktraceData* fdata = (BacktraceData*) data;
    StackFrame* frame = fdata->currentFrame;

    frame->line = line;
    cstring::copy(frame->function, MAX_TRACE_FUNCTION, fn);
    cstring::copy(frame->filename, MAX_TRACE_FILENAME, file);

    free(realname);

    if (fdata->frameNumber > 0)
    {
        StackFrame* prevFrame = &m_stackFrames[fdata->frameNumber-1];
        prevFrame->next = frame;
        frame->prev = prevFrame;
    }

    StackFrame* nextFrame = &m_stackFrames[fdata->frameNumber+1];
    fdata->frameNumber = fdata->frameNumber+1;
    nextFrame->next = nullptr;
    nextFrame->prev = nullptr;

    fdata->currentFrame = nextFrame;

    return 0;
}

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
int platform::exec(const char* program, const char* args)
{
    int status = -1;

    if (args)
    {
        char cmd[MAX_CMD_LENGTH];
        cstring::format(cmd, MAX_CMD_LENGTH, "%s %s", program, args);
        
        status = ::system(cmd);
    }
    else
    {
        status = ::system(program);
    }

    return status;
}

// -----------------------------------------------------------------------------

size_t platform::page_size()
{
    return ::sysconf(_SC_PAGE_SIZE);
}

// -----------------------------------------------------------------------------

StackFrame* platform::backtrace(int skip)
{
    char buffer[512];
    get_executable_path(buffer, 512);
    
    StackFrame* frame = &m_stackFrames[0];
    backtrace_state* state = backtrace_create_state(buffer, 0, nullptr, nullptr);
    
    if (state != nullptr)
    {
        frame->next = nullptr;
        frame->prev = nullptr;

        BacktraceData data;
        data.currentFrame = frame;
        data.frameNumber = 0;

        backtrace_full(state, skip, full_backtrace_callback, nullptr, &data);
    }
    else
    {
        frame = nullptr;
    }

    return frame;
}

// -----------------------------------------------------------------------------

void platform::print_backtrace(StackFrame* btframe)
{
    StackFrame* frame = btframe;

    while (frame != nullptr)
    {
        printf("%s\t%s:%d\n", frame->function, frame->filename, frame->line);
        frame = frame->next;
    }
}

}   // namespace bw