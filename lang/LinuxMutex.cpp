#ifdef LINUX

#include <cassert>
#include <lang/Exception.h>
#include <lang/Mutex.h>

Mutex::Mutex() {

  int res = 0;
  res = pthread_mutexattr_init(&mutexAttr);

  res = pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_RECURSIVE);
  assert(res == 0);

  res = pthread_mutex_init(&mutex, &mutexAttr);
  assert(res == 0);
}

Mutex::~Mutex() {
  int res = pthread_mutex_destroy(&mutex);
  if (res != 0) {
    throw(Exception(
        "LinuxMutex::~LinuxMutex() - mutex in deconstructor still locked",
        __FILE__, __LINE__));
  }

  res = pthread_mutexattr_destroy(&mutexAttr);
  assert(res == 0);
}

void Mutex::lock() {
  int res = 0;
  // res = pthread_mutex_trylock(&mutex);
  //  std::cout << "trylock: " << res << std::endl;

  res = pthread_mutex_lock(&mutex);
  if (res != 0) {
    throw(Exception("LinuxMutex::lock - could not lock", __FILE__, __LINE__));
  }
}

void Mutex::unlock() {
  int res = pthread_mutex_unlock(&mutex);
  if (res != 0) {
    throw(
        Exception("LinuxMutex::unlock - could not unlock", __FILE__, __LINE__));
  }
}

pthread_mutex_t* Mutex::getMutex() { return (&mutex); }

#endif // LINUX
