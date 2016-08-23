#include <lang/Exception.h>
#include <lang/Thread.h>

#include <lang/Event.h>

int Thread::LOW = 0;
int Thread::NORMAL = 1;
int Thread::HIGH = 2;

Thread::~Thread() {}

void* Thread::startThread(void* arg) {
  Thread* thread = (Thread*)arg;
  thread->run();
  return (0);
}

void* Thread::startRunnable(void* arg) {
  Thread* thread = (Thread*)arg;
  thread->runnable->run();
  return (0);
}

void Thread::sleep(unsigned long millis) {
  Event e;
  e.wait(millis);
}

void Thread::yield() {
  Event e;
  e.wait(0);
}

void Thread::start() {
  int res = 0;
  if (runnable == 0) {
    res = ::pthread_create(&threadHandle,
                           NULL,                // attribute
                           Thread::startThread, // startmethode
                           this);               // startargument
  } else {
    res = ::pthread_create(&threadHandle,
                           NULL,                  // attribute
                           Thread::startRunnable, // startmethode
                           this);                 // startargument
  }
  if (res != 0) {
    throw(Exception("could not created thread", __FILE__, __LINE__));
  }
}

void Thread::join() {
  int res = 0;
  void* threadResult;
  res = ::pthread_join(threadHandle, &threadResult);
  if (res != 0) {
    throw Exception("could not join thread", __FILE__, __LINE__);
  }
}
