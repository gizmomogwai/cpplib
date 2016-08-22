#ifdef LINUX

#include <lang/SyncMutex.h>
#include <assert.h>
#include <lang/Exception.h>

SyncMutex::SyncMutex() {

  // klappt immer
  int res = pthread_cond_init(&condition, 0);
  assert(res == 0);
}

SyncMutex::~SyncMutex() {
  int res = pthread_cond_destroy(&condition);
  
  if (res != 0) {
    throw(Exception("SyncMutex::~SyncMutex - could not destroy condition", 
                    __FILE__, __LINE__));
  }
}

void SyncMutex::lock() {
  mutex.lock();
}


void SyncMutex::unlock() {
  mutex.unlock();
}

void SyncMutex::wait() {
  int res = pthread_cond_wait(&condition, mutex.getMutex());
  if (res != 0) {
    throw(Exception("SyncMutex::wait - could not wait", 
                    __FILE__, __LINE__));
  }
}

void SyncMutex::notify() {
  int res = pthread_cond_signal(&condition);
  if (res != 0) {
    throw(Exception("SyncMutex::notify - could not notify", 
                    __FILE__, __LINE__));
  }
}

#endif
