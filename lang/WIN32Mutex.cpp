#ifdef WIN32

#include <lang/Mutex.h>
#include <lang/Exception.h>

#include <iostream>
  
Mutex::Mutex() {
#ifdef _mutex_
  mutex = CreateMutex(NULL, //  security
                      false, // initial owner
                      NULL); // objectname
  if (mutex == NULL) {
    throw(Exception("Mutex failed", __FILE__, __LINE__));
  }
#endif
#ifdef _criticalSection_
  InitializeCriticalSection(&criticalSection);
#endif
#ifdef _cCriticalSection_

#endif
}


Mutex::~Mutex() {
#ifdef _mutex_
  CloseHandle(mutex);
#endif
#ifdef _criticalSection_
  DeleteCriticalSection(&criticalSection);
#endif
#ifdef _cCriticalSection_
#endif
}

void Mutex::lock() {
#ifdef _mutex_
  DWORD res = WaitForSingleObject(mutex, INFINITE);
  switch (res) {
    case WAIT_FAILED:
      std::cout << "Mutex lock failed" << std::endl;
      throw(Exception("Mutex::lock failed", __FILE__, __LINE__));
    case WAIT_OBJECT_0:
      // normaler fall
      break;
    case WAIT_ABANDONED:
      std::cout << "Mutex lock abandoned" << std::endl;
      throw(Exception("Mutex::lock - abandoned", __FILE__, __LINE__));
    case WAIT_TIMEOUT:
      std::cout << "Mutex lock time out" << std::endl;
      throw(Exception("Mutex::lock - timeout", __FILE__, __LINE__));
  }
#endif
#ifdef _criticalSection_
  EnterCriticalSection(&criticalSection);
#endif
#ifdef _cCriticalSection_
  criticalSection.Lock();
#endif
}

void Mutex::unlock() {
#ifdef _mutex_
  ReleaseMutex(mutex);
#endif
#ifdef _criticalSection_
  LeaveCriticalSection(&criticalSection);
#endif
#ifdef _cCriticalSection_
  criticalSection.Unlock();
#endif
}

#endif // WIN32
