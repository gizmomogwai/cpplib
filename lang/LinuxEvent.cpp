#ifdef LINUX

#include <lang/Event.h>
#include <lang/Exception.h>
#include <sys/time.h>
#include <unistd.h>
//#include <asm/errno.h> // for ETIMEDOUT
#include <assert.h>

Event::Event() : mutex(new Mutex()), eventSet(false) {
  // klappt immer
  int res = pthread_cond_init(&condition, 0);
  assert(res == 0);
}

Event::~Event() {
  int res = pthread_cond_destroy(&condition);
  if (res != 0) {
    throw(Exception(
        "Event::~Event() - could not destroy cond - someones waiting!",
        __FILE__, __LINE__));
  }

  if (mutex != 0) {
    delete (mutex);
    mutex = 0;
  }
}

void Event::wait() {
  AutoMutex lock(mutex);

  if (eventSet == false) {
    // klappt immer
    int res = pthread_cond_wait(&condition, mutex->getMutex());
    assert(res == 0);
  }
}

bool Event::wait(unsigned long time) {
  AutoMutex lock(mutex);

  int res = true;
  if (eventSet == false) {

    // timeval hat sekunden und microsekunden
    // simespec hat sekunden und nanosekunden
    struct timeval now;
    struct timespec timeOut;

    // timezone egal bzw. linux kann das gar nicht
    gettimeofday(&now, 0);

    // calc endtime
    int s = time / 1000;
    time -= s * 1000;
    now.tv_sec += s;
    now.tv_usec += time * 1000;

    // normalerweise mit TIMEVAL_TO_TIMESPEC ..
    // aber suse kann das nicht????
    timeOut.tv_sec = now.tv_sec;
    timeOut.tv_nsec = now.tv_usec * 1000;

    int ret = pthread_cond_timedwait(&condition, mutex->getMutex(), &timeOut);
    if (ret == ETIMEDOUT) {
      res = false;
    }
  }

  return (res);
}

void Event::notify() {
  AutoMutex lock(mutex);

  int res = pthread_cond_signal(&condition);
  assert(res == 0);
}

void Event::setEvent() {
  AutoMutex lock(mutex);

  eventSet = true;
  int res = pthread_cond_broadcast(&condition);
  assert(res == 0);
}

#endif // LINUX
