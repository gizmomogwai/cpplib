#ifndef IoApi_h_
#define IoApi_h_

#include <LibHandling.h>

#ifdef BUILD_IO_API
#  define IO_API 
#else
#  define IO_API DLL_IMPORT
#endif

#endif
