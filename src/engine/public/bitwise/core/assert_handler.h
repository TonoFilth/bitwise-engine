#pragma once

#include "bitwise/core/export.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  AssertHandler
////////////////////////////////////////////////////////////////////////////////
class BW_API AssertHandler
{
public:
    virtual ~AssertHandler() = default;
    virtual void operator()(const char* exp, const char* file, int line) = 0;
};

}   // namespace bw