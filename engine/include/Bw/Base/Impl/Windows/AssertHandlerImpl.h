#ifndef BW_BASE_ASSERT_HANDLER_IMPL_H
#define BW_BASE_ASSERT_HANDLER_IMPL_H

#include "Bw/Base/Assert.h"
#include "Bw/Base/Export.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
// AssertHandlerImpl
////////////////////////////////////////////////////////////////////////////////
class BW_BASE_API AssertHandlerImpl : public AssertHandler
{
public:
	AssertHandlerImpl();
	virtual ~AssertHandlerImpl() = default;

	void operator()(const char* exp, const char* file, int line) override;
};

}	// namespace bw

#endif	// BW_BASE_ASSERT_HANDLER_IMPL_H