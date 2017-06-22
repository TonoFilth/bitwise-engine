#include "bitwise/core/callstack.h"
#include "bitwise/core/internal.h"
#include "bitwise/core/cstring.h"
#include "bitwise/core/assert.h"

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static bw::callstack::StackFrameFormatter m_formatter = bw::internal::default_stack_frame_formatter;

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------
static size_t bw::internal::default_stack_frame_formatter(bw::StackFrame& frame, char* buffer, size_t bufferSize)
{
    return bw::cstring::format(buffer, bufferSize, "#%u | %s %s:%u\n", frame.depth, frame.function, frame.filename, frame.line);
}

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
callstack::StackFrameFormatter callstack::set_stack_frame_formatter(callstack::StackFrameFormatter formatter)
{
    StackFrameFormatter prevFormatter = m_formatter;

    if (formatter != nullptr)
    {
        m_formatter = formatter;
    }
    else
    {
        m_formatter = internal::default_stack_frame_formatter;
    }

    return prevFormatter;
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