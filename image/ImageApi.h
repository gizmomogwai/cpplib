#ifndef ImageApi_h_
#define ImageApi_h_

#include <LibHandling.h>

#ifdef BUILD_IMAGE_API
#  define IMAGE_API
#else
#  define IMAGE_API DLL_IMPORT
#endif

#endif
