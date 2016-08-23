#ifdef LINUX

#include <lang/SysError.h>

#include <errno.h>

void SysError::throwDetailedException(std::string base) throw(Exception) {
  std::string msg = base;
  msg += " - ";
  //#include "../linux/LinuxSysError.inc"

  Exception e(msg, __FILE__, __LINE__);
  throw(e);
}

#endif // LINUX
