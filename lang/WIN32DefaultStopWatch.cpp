#ifdef WIN32

#include <lang/DefaultStopWatch.h>


DefaultStopWatch::DefaultStopWatch() {
  startTime = 0;
  endTime = 0;
}

DefaultStopWatch::~DefaultStopWatch() {
}

void DefaultStopWatch::start() {
  startTime = GetTickCount();
}

void DefaultStopWatch::stop() {
  endTime = GetTickCount();
}

double DefaultStopWatch::getDelta() {
  return(endTime - startTime);
}

#endif // WIN32
