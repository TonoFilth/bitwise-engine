#ifndef BW_FOUNDATION_EXPORT_H
#define BW_FOUNDATION_EXPORT_H

#include "Bw/Base/Preprocessor.h"

#if defined(BW_FOUNDATION_EXPORT)
#	define BW_FOUNDATION_API BW_API_EXPORT
#else
#	define BW_FOUNDATION_API BW_API_IMPORT
#endif

#endif	// BW_FOUNDATION_EXPORT_H