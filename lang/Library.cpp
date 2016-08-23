#include <lang/Library.h>

#ifdef LINUX
#include <lang/Library.Linux>
#elif WIN32
#include <lang/Library.W32>
#endif
