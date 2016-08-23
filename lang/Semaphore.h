#pragma once

#ifdef WIN32
#include <lang/Event.h>
#include <lang/Mutex.h>

class Semaphore {
public:
  Semaphore(unsigned int available) : fAvailable(available) {}

  void aquire(unsigned int nrOfItems) {
    fMutex.lock();

    while (fAvailable <= nrOfItems) {
      fMutex.unlock();
      fCondition.wait();
      fMutex.lock();
    }
    fAvailable -= nrOfItems;
    fMutex.unlock();
  }

  void release(unsigned int nrOfItems) {
    AutoMutex lock(&fMutex);
    fCondition.reset();
    fAvailable += nrOfItems;
    fCondition.setEvent();
  }

  unsigned int getCount() {
    AutoMutex lock(&fMutex);

    return fAvailable;
  }

private:
  Mutex fMutex;
  Event fCondition;
  unsigned int fAvailable;
};

#endif

#ifdef LINUX
#include <cassert>

#include <lang/Mutex.h>

class Condition {
public:
  Condition() {
    int res = pthread_cond_init(&fCondition, 0);
    assert(0 == res);
  }

  ~Condition() {
    int res = pthread_cond_destroy(&fCondition);
    assert(0 == res);
  }

  void wait(Mutex &mutex) {
    int res = pthread_cond_wait(&fCondition, mutex.getMutex());
    assert(0 == res);
  }

  void notify(Mutex &mutex) {
    int res = pthread_cond_signal(&fCondition);
    assert(0 == res);
  }

private:
  pthread_cond_t fCondition;
};

class Semaphore {

public:
  Semaphore(unsigned int available) : fAvailable(available) {}

  void aquire(unsigned int nrOfItems) {
    AutoMutex lock(&fMutex);

    while (fAvailable <= nrOfItems) {
      fCondition.wait(fMutex);
    }
    fAvailable -= nrOfItems;
  }

  void release(unsigned int nrOfItems) {
    AutoMutex lock(&fMutex);

    fAvailable += nrOfItems;
    fCondition.notify(fMutex);
  }
  unsigned int getCount() {
    AutoMutex lock(&fMutex);

    return fAvailable;
  }

private:
  Mutex fMutex;
  Condition fCondition;
  unsigned int fAvailable;
};

#endif
