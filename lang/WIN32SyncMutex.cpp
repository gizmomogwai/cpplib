#include <lang/SyncMutex.h>

#include <assert.h>

#ifdef WIN32
SyncMutex::SyncMutex() : waiting(false) {
}

SyncMutex::~SyncMutex() {
}

void SyncMutex::lock() {

  m.lock();
}

void SyncMutex::unlock() {

  m.unlock();
}

void SyncMutex::wait() {

  assert(waiting == false);
  waiting = true;  

  m.unlock();

  e.wait();
  
  m.lock();
}

void SyncMutex::notify() {

  if (waiting == true) {

    waiting = false;
    e.setEvent();
  }
}

#endif
