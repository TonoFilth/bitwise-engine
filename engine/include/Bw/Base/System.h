#ifndef BW_BASE_SYSTEM_H
#define BW_BASE_SYSTEM_H

#include "Bw/Base/Common/Module.h"

namespace bw
{
namespace system
{

BW_BASE_API I32 exec(const char* program, const char* args);

}   // namespace system
}   // namespace bw

#endif  // BW_BASE_SYSTEM_H