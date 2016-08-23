#ifdef LINUX

#include <lang/HPStopWatch.h>

#include <lang/Exception.h>

HPStopWatch::HPStopWatch() {}

HPStopWatch::~HPStopWatch() {}

void HPStopWatch::start() {
  int res = gettimeofday(&startTime, 0);
  if (res != 0) {
    throw(Exception("HPStopWatch::stop - could not take time", __FILE__,
                    __LINE__));
  }
}

void HPStopWatch::stop() {
  int res = gettimeofday(&endTime, 0);
  if (res != 0) {
    throw(Exception("HPStopWatch::stop - could not take time", __FILE__,
                    __LINE__));
  }
}

double HPStopWatch::getDelta() {
  struct timeval delta;
  timersub(&endTime, &startTime, &delta);
  double res = delta.tv_sec * 1000 + delta.tv_usec / 1000;
  return res;
}

double HPStopWatch::getCurrent() {
  struct timeval current;
  int res = gettimeofday(&current, 0);
  if (res != 0) {
    throw(Exception("HPStopWatch::stop - could not take time", __FILE__,
                    __LINE__));
  }
  return current.tv_sec * 1000 + current.tv_usec / 1000;
}

double HPStopWatch::getRealTime(double start, double end) {
  return end - start;
}

#endif // LINUX
