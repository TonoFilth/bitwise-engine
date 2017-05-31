#ifndef BW_BASE_ASSERT_H
#define BW_BASE_ASSERT_H

#include "Bw/Base/Export.h"
#include "Bw/Base/Types.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API AssertHandler& GetAssertHandler();
BW_BASE_API AssertHandler& SetAssertHandler(AssertHandler* handler);

}	// namespace bw

////////////////////////////////////////////////////////////////////////////////
//  Assert macro
////////////////////////////////////////////////////////////////////////////////
#if defined(BW_DEBUG)
	#define BW_ASSERT(exp, ...) do { if (!(exp)) bw::GetAssertHandler()(#exp, __FILE__, __LINE__); } while(0)
#else
	#define BW_ASSERT(expr, ...) do {} while(0)
#endif

#endif	// BW_BASE_ASSERT_H