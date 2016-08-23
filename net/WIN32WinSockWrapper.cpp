#ifdef WIN32

#include <net/WIN32WinSockWrapper.h>

#include <iostream>
#include <lang/Exception.h>

Mutex WinSockWrapper::m;

int WinSockWrapper::refCount = 0;

void WinSockWrapper::init() {
  m.lock();
  if (refCount == 0) {
    WSADATA winSocketData;
    if (WSAStartup(MAKEWORD(1, 1), &winSocketData) != 0) {
      throw(Exception("Initialising WinSock", __FILE__, __LINE__));
    }
  }
  refCount++;
  m.unlock();
}

void WinSockWrapper::deinit() {
  m.lock();
  refCount--;
  if (refCount == 0) {
    WSACleanup();
  }
  m.unlock();
}

#endif // WIN32
