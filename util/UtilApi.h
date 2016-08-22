#ifndef UtilApi_h_
#define UtilApi_h_

#include <LibHandling.h>

#ifdef BUILD_UTIL_API
#  define UTIL_API
#else
#  define UTIL_API DLL_IMPORT
#endif

#endif
