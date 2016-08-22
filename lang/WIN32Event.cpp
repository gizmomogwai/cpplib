#ifdef WIN32

#include <lang/Event.h>

#include <lang/Exception.h>
#include <iostream>

Event::Event() {
  event = CreateEvent(NULL, // no security
                      FALSE, // manual reset
                      FALSE, // initial state is not signaled
                      NULL); // kein name
  if (event == NULL) {
    throw(Exception("Event::Event - could not create eventhandle.", 
                    __FILE__, __LINE__));
  }
}

Event::~Event() {
  BOOL res = CloseHandle(event);
  if (res == 0) {
    throw(Exception("Event::~Event - error while closing handle", 
                    __FILE__, __LINE__));
  }

}

void Event::wait() {
  DWORD res = WaitForSingleObject(event, INFINITE);
  switch (res) {
    case WAIT_ABANDONED:
      throw(Exception("Event::wait - abandoned", __FILE__, __LINE__));
    case WAIT_TIMEOUT:
      throw(Exception("Event::wait - timeout", __FILE__, __LINE__));
  }
}

bool Event::wait(unsigned long millis) {
  DWORD res = WaitForSingleObject(event, (DWORD)millis);
  switch (res) {
    case WAIT_ABANDONED:
      std::cout << "Event::wait(unsigned long) - wait abandoned " 
        << ".. ist das gut" << std::endl;
      return(true);
    case WAIT_OBJECT_0:
      return(true);
    case WAIT_TIMEOUT:
      return(false);
    default:
      throw(Exception("Event::wait(unsigned long) - damit hab ich nciht gerechnet", 
                      __FILE__, __LINE__));
  }
}

void Event::notify() {
  BOOL res = PulseEvent(event);  
  if (res == 0) {
    throw(Exception("Event::notify - could not signal event", 
                    __FILE__, __LINE__));
  }
}

void Event::setEvent() {
  BOOL res = SetEvent(event);  
  if (res == 0) {
    throw(Exception("Event::setEvent - could not signal event", 
                    __FILE__, __LINE__));
  }
}

void Event::reset() {
	BOOL res = ResetEvent(event);
	if (res == 0) {
		throw Exception("Event::resetEvent - could not reset event", __FILE__, __LINE__);
	}
}
#endif // WIN32
