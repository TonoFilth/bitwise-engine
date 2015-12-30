#ifndef BW_BASE_SYSTEM_H
#define BW_BASE_SYSTEM_H

#include "Bw/Base/Common/Module.h"

namespace bw
{
namespace system
{

BW_BASE_API int32_t exec(const char* program, const char* args);
BW_BASE_API size_t  get_page_size();

}   // namespace system
}   // namespace bw

#endif  // BW_BASE_SYSTEM_H