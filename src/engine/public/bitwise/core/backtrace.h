#pragma once

#include <cstddef>  // size_t

namespace bw
{

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
const size_t MAX_TRACE_FUNCTION = 256;
const size_t MAX_TRACE_FILENAME = 256;

////////////////////////////////////////////////////////////////////////////////
//  StackFrame
////////////////////////////////////////////////////////////////////////////////
struct StackFrame
{
    char function[MAX_TRACE_FUNCTION];
    char filename[MAX_TRACE_FILENAME];
    unsigned line;
    
    StackFrame* next;
    StackFrame* prev;
};

}   // namespace bw