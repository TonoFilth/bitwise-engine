#ifndef BW_BASE_DEFAULT_ASSERT_HANDLER_H
#define BW_BASE_DEFAULT_ASSERT_HANDLER_H

#include "Bw/Base/Types.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
// DefaultAssertHandler
////////////////////////////////////////////////////////////////////////////////
class BW_BASE_API DefaultAssertHandler : public AssertHandler
{
public:
    DefaultAssertHandler();
    virtual ~DefaultAssertHandler() = default;

	DefaultAssertHandler(const DefaultAssertHandler& toCopy)            = delete;
    DefaultAssertHandler& operator=(const DefaultAssertHandler& toCopy) = delete;

public:
    void operator()(const char* exp, const char* file, int line) override;
};

}   // namespace bw

#endif  // BW_BASE_DEFAULT_ASSERT_HANDLER_H