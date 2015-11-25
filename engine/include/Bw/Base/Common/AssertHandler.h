#ifndef BW_BASE_ASSERT_HANDLER_H
#define BW_BASE_ASSERT_HANDLER_H

#include "Bw/Base/Common/Export.h"
#include "Bw/Base/Common/ModuleTypes.h"

namespace bw
{
namespace assert_handler
{

////////////////////////////////////////////////////////////////////////////////
//  Assert handler functions
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API AssertHandler& get();
BW_BASE_API AssertHandler& set(AssertHandler& handler);
BW_BASE_API AssertHandler& reset_default();

}	// namespace assert_handler
}	// namespace bw

////////////////////////////////////////////////////////////////////////////////
//  Assert macro
////////////////////////////////////////////////////////////////////////////////
#if defined(BW_DEBUG)
	#define BW_ASSERT(exp, ...) do { if (!(exp)) bw::assert_handler::get()(#exp, __FILE__, __LINE__); } while(0)
#else
	#define BW_ASSERT(expr, ...) do {} while(0)
#endif

#endif	// BW_BASE_ASSERT_HANDLER_H