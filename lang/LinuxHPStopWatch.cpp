#if defined(LINUX) || defined(OSX)

#include <lang/HPStopWatch.h>

#include <lang/Exception.h>

HPStopWatch::HPStopWatch() {}

HPStopWatch::~HPStopWatch() {}

StopWatch& HPStopWatch::start() {
  int res = gettimeofday(&startTime, 0);
  if (res != 0) {
    throw(Exception("HPStopWatch::stop - could not take time", __FILE__,
                    __LINE__));
  }
  return *this;
}

StopWatch& HPStopWatch::stop() {
  int res = gettimeofday(&endTime, 0);
  if (res != 0) {
    throw(Exception("HPStopWatch::stop - could not take time", __FILE__,
                    __LINE__));
  }
  return *this;
}

double HPStopWatch::getDelta() {
  struct timeval delta;
  timersub(&endTime, &startTime, &delta);
  double res = delta.tv_sec * 1000 + delta.tv_usec / 1000;
  return res;
}

int64_t HPStopWatch::getCurrent() {
  struct timeval current;
  int res = gettimeofday(&current, 0);
  if (res != 0) {
    throw(Exception("HPStopWatch::stop - could not take time", __FILE__,
                    __LINE__));
  }
  int64_t time = current.tv_sec * 1000 + current.tv_usec / 1000;
  return time;
}

double HPStopWatch::getRealTime(double start, double end) {
  return end - start;
}

#endif // LINUX
