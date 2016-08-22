#ifdef WIN32

#include <lang/Thread.h>

#include <lang/Exception.h>

int Thread::LOW = 0;
int Thread::NORMAL = 1;
int Thread::HIGH = 2;

Thread::~Thread() {
  if (threadHandle != 0) {
    CloseHandle(threadHandle);
		threadHandle = 0;
  }
}

unsigned long __stdcall Thread::startThread(void* arg) {
  Thread* thread = (Thread*)arg;
  thread->run();
  return(0);
}


unsigned long __stdcall Thread::startRunnable(void* arg) {
  Thread* thread = (Thread*)arg;
  thread->runnable->run();
	delete(thread);
  return(0);
}


void Thread::sleep(unsigned long millis) {
  Sleep((DWORD)millis);
}

void Thread::yield() {
  Sleep(0);
}

void Thread::start() {

	if (runnable == 0) {
		threadHandle = ::CreateThread(0, // keine securitysachen
																	0, // nix an der stacksize drehen
																	Thread::startThread, // threadmethode
																	this, // threadargumente
																	0, // gleich loslaufen
																	&threadID); // threadid merken

	} else {
		threadHandle = ::CreateThread(0, // keine securitysachen
																	0, // nix an der stacksizedrehen
																	Thread::startRunnable, // threadmethode
																	this, // thread argumente
																	0, // gleich loslaufen
																	&threadID); // threadid merken
	}
	if(threadHandle == 0) {
		throw(Exception("could not create thread", __FILE__, __LINE__));
	}

  BOOL res = 1;
  if (priority == LOW) {
    res = ::SetThreadPriority(threadHandle, THREAD_PRIORITY_BELOW_NORMAL);
  } else if (priority == HIGH) {
    res = ::SetThreadPriority(threadHandle, THREAD_PRIORITY_ABOVE_NORMAL);
  }
  if (res == 0) {
    throw(Exception("could not change thread priority"));
  }

}

void Thread::join() {
	DWORD res = WaitForSingleObject(threadHandle, INFINITE);
	if (res != WAIT_OBJECT_0) {
		throw Exception("WAIT_OBJECT_0 expected");
	}
}

#endif // WIN32
