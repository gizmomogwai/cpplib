#ifdef WIN32

#include <lang/HPStopWatch.h>
#include <lang/Exception.h>

#ifdef _AFX
  #include <AfxWin.h>
#endif
#ifdef _COMMAND
  #include <windows.h>
#endif

#include <iostream>

HPStopWatch::HPStopWatch() : f(0), startTime(0), endTime(0) {
  // check for high resolution timer
  LARGE_INTEGER help;
  BOOL res = QueryPerformanceFrequency(&help);
  if (res == 0) {
    throw(Exception("StopWatch::PerformanceCounter nicht unterstuetzt", 
                    __FILE__, __LINE__));
  }
  f = 1000/(double)help.QuadPart ;
}

HPStopWatch::~HPStopWatch() {
}

double HPStopWatch::getCurrent() {
  
  LARGE_INTEGER li;
  BOOL res = QueryPerformanceCounter(&li);
  if (res == 0) {
    throw(Exception("StopWatch::PerformanceCounter nicht unterstuetzt", 
                                __FILE__, __LINE__));
  }
  double ret = (double)li.QuadPart;
  return(ret);
}


void HPStopWatch::start() {
  startTime = getCurrent();
}

void HPStopWatch::stop() {
  endTime = getCurrent();
}

double HPStopWatch::getDelta() {
  return getRealTime(startTime, endTime);
}

double HPStopWatch::getRealTime(double start, double end) {
  double res = (end-start) * f;
  return res;
}

#endif // WIN32
