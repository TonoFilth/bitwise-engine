#ifndef BW_BASE_CONSOLE_H
#define BW_BASE_CONSOLE_H

#include "Bw/Base/Export.h"

namespace bw
{
namespace Console
{

////////////////////////////////////////////////////////////////////////////////
//	Public functions
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API void Write      (const char* text);
BW_BASE_API void WriteLine  (const char* text);
BW_BASE_API void WriteFormat(const char* format, ...);

}	// namespace Console
}	// namespace bw

#endif	// BW_BASE_CONSOLE_H