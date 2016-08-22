#include <sg/conditions/WakeupOnElapsedFrames.h>

WakeupOnElapsedFrames::WakeupOnElapsedFrames(int frames) 
  : n(frames), current(frames) {
}


bool WakeupOnElapsedFrames::evaluate() {

  bool res = false;
  if (current == 0) {
    res = true;
    current = n;
  } else {
    current--;
  }

  return(res);
}
