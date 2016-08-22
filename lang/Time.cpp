#include <lang/Time.h>

#ifdef WIN32

#include <lang/Exception.h>

#ifdef _AFX
  #include <AfxWin.h>
#endif
#ifdef _COMMAND
  #include <windows.h>
#endif


Time::Time() {
  LARGE_INTEGER help;
  BOOL res = QueryPerformanceFrequency(&help);
  if (res == 0) {
    throw(Exception("StopWatch::PerformanceCounter nicht unterstuetzt", 
                    __FILE__, __LINE__));
  }
  f = 1000.0 / (double)help.QuadPart ;
}

Time::~Time() {
}

double Time::getCurrentTimeMicros() {
  LARGE_INTEGER li;
  BOOL res = QueryPerformanceCounter(&li);
  if (res == 0) {
    throw(Exception("StopWatch::PerformanceCounter nicht unterstuetzt", 
                                __FILE__, __LINE__));
  }
	return(((double)li.QuadPart) * f);
}

#endif
