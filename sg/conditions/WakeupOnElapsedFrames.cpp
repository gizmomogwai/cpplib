#include <sg/conditions/WakeupOnElapsedFrames.h>

WakeupOnElapsedFrames::WakeupOnElapsedFrames(int frames)
  : n(frames), current(frames) {
}

bool WakeupOnElapsedFrames::evaluate() {
  if (current == 0) {
    current = n;
    return true;
  } else {
    current--;
    return false;
  }
}
