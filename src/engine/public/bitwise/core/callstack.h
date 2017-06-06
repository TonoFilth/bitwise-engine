#pragma once

#include <cstddef>  // size_t
#include "bitwise/core/export.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  StackFrame
////////////////////////////////////////////////////////////////////////////////
struct StackFrame
{
    static const size_t MAX_FUNCTION_NAME = 128;
    static const size_t MAX_FILE_NAME     = 256;

    char function[MAX_FUNCTION_NAME];
    char filename[MAX_FILE_NAME];
    unsigned line;
    
    StackFrame* next;
    StackFrame* prev;
};

namespace callstack
{
    BW_API StackFrame* walk(int skip = 0);
    BW_API void        print(StackFrame* frame);

}   // namespace system
}   // namespace bw