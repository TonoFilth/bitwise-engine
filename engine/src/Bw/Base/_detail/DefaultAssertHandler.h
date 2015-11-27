#ifndef BW_BASE_DEFAULT_ASSERT_HANDLER_H
#define BW_BASE_DEFAULT_ASSERT_HANDLER_H

#include "Bw/Base/Common/ModuleTypes.h"

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

    void operator()(const char* exp, const char* file, int line) override;

private:
    // DefaultAssertHandler cannot be copied
    DefaultAssertHandler(const DefaultAssertHandler& toCopy);
    DefaultAssertHandler& operator=(const DefaultAssertHandler& toCopy);
};

}   // namespace bw

#endif  // BW_BASE_DEFAULT_ASSERT_HANDLER_H
