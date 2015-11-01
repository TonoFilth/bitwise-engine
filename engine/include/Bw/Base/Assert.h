#ifndef BW_BASE_ASSERT_H
#define BW_BASE_ASSERT_H

#include "Bw/Base/Export.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
// AssertHandler
////////////////////////////////////////////////////////////////////////////////
class AssertHandler
{
public:
	virtual ~AssertHandler() = default;
	virtual void operator()(const char* exp, const char* file, int line) = 0;
};

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API AssertHandler& GetAssertHandler();
BW_BASE_API void           SetAssertHandler(AssertHandler& handler);

}	// namespace bw

////////////////////////////////////////////////////////////////////////////////
//  Macros
////////////////////////////////////////////////////////////////////////////////
#if defined(BW_DEBUG)
	#define BW_ASSERT(exp, ...) do { if (!(exp)) bw::GetAssertHandler()(#exp, __FILE__, __LINE__); } while(0)
#else
	#define BW_ASSERT(expr, ...) do {} while(0)
#endif

#endif	// BW_BASE_ASSERT_H