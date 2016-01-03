#ifndef BW_BASE_SYSTEM_H
#define BW_BASE_SYSTEM_H

#include "Bw/Base/Common/Export.h"
#include "Bw/Base/Common/Types.h"

namespace bw
{
namespace System
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API int32_t Exec(const char* program, const char* args);
BW_BASE_API size_t  GetPageSize();

}   // namespace System
}   // namespace bw

#endif  // BW_BASE_SYSTEM_H