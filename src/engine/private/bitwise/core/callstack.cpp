#include "bitwise/core/callstack.h"
#include "bitwise/core/internal.h"
#include "bitwise/core/cstring.h"
#include "bitwise/core/assert.h"

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const size_t kMaxCallstackBuffer = 2048;

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static char m_callstackBuffer[kMaxCallstackBuffer];
static bw::callstack::StackFrameFormatter m_formatter = bw::internal::callstack::default_formatter;

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------
static size_t bw::internal::callstack::default_formatter(bw::StackFrame& frame, char* buffer, size_t bufferSize)
{
    return bw::cstring::format(buffer, bufferSize, "#%u | %s Line %u\n", frame.depth, frame.function, frame.line);
}

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
callstack::StackFrameFormatter callstack::stack_frame_formatter()
{
    return m_formatter;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
callstack::StackFrameFormatter callstack::stack_frame_formatter(callstack::StackFrameFormatter formatter)
{
    StackFrameFormatter prevFormatter = m_formatter;

    if (formatter != nullptr)
    {
        m_formatter = formatter;
    }
    else
    {
        m_formatter = bw::internal::callstack::default_formatter;
    }

    return prevFormatter;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
const char* callstack::to_string(int skip)
{
    StackFrame* frame = bw::callstack::walk(skip);

    if (frame != nullptr)
    {
        bw::callstack::to_string(*frame, m_callstackBuffer, kMaxCallstackBuffer);
    }
    else
    {
        bw::cstring::copy(m_callstackBuffer, kMaxCallstackBuffer, "Can't walk the callstack");
    }

    return m_callstackBuffer;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t callstack::to_string(char* buffer, size_t bufferSize, int skip)
{
    StackFrame* frame = bw::callstack::walk(skip);

    if (frame != nullptr)
    {
        return bw::callstack::to_string(*frame, buffer, bufferSize);
    }
    else
    {
        bw::cstring::copy(buffer, bufferSize, "Can't walk the callstack");
        return bw::cstring::length(buffer);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t callstack::to_string(StackFrame& frame, char* buffer, size_t bufferSize)
{
    size_t nbChars = 0;
    StackFrame* f = &frame;

    char* buff = buffer;
    size_t remainingSize = bufferSize;

    while (f != nullptr && remainingSize > 0)
    {
        size_t nchars = m_formatter(*f, buff, remainingSize);

        buff    += nchars;
        nbChars += nchars;
        remainingSize -= nchars;

        f = f->next;
    }

    return nbChars;
}

}	// namespace bw