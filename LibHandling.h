#ifndef LibHandling_h_
#define LibHandling_h_

#if defined (WIN32)
  #define DLL_EXPORT __declspec(dllexport)
  #define DLL_IMPORT __declspec(dllimport)
#elif defined (LINUX) || defined (OSX)
  #define DLL_EXPORT
  #define DLL_IMPORT
#else
  #error "OS not defined"
#endif

#endif
