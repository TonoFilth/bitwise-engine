#pragma once

#include "bitwise/core/assert_handler.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
// DefaultAssertHandler
////////////////////////////////////////////////////////////////////////////////
class BW_API DefaultAssertHandler : public AssertHandler
{
public:
    DefaultAssertHandler();
    virtual ~DefaultAssertHandler();

    DefaultAssertHandler(const DefaultAssertHandler& other)            = delete;
    DefaultAssertHandler& operator=(const DefaultAssertHandler& other) = delete;

public:
    void operator()(const char* exp, const char* file, int line) override;
};

}   // namespace bw