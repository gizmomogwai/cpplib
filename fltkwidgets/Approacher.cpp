#include "Approacher.h"

float LinearApproacher::approach(const float current, const float target) {
  const float minApproach = 0.05f;
  float delta = (target - current) / 5;
  if (delta > 0) {
    if (delta < minApproach) {
      delta = minApproach;
    }
  } else if (delta < 0) {
    if (delta > -minApproach) {
      delta = -minApproach;
    }
  }
  
  float res = current + delta;
  if (delta > 0) {
    if (res > target) {
      res = target;
    }
  } else if (delta < 0) {
    if (res < target) {
      res = target;
    }
  }

  return res;
}

SpringApproacher::SpringApproacher() : fV(0.0f) {}
float SpringApproacher::approach(const float current, const float target) {
  float time = 0.2f;
  float f = (target - current) * 5.0f; // federkraft
  float a = f; // masse == 1
  fV = fV * 0.85f; // daempfung
  fV = fV + a * time; // 
  float delta = time * fV;
  float res = current + delta;
  
  return res;
}


BouncingApproacher::BouncingApproacher() : fV(0.0f) {}
float BouncingApproacher::approach(const float current, const float target) {
  float time = 0.2f;
  float f = (target - current) * 0.5f;
  float a = f;
  fV = fV * 0.8f;
  fV = fV + a * time;
  
  float res = current + time * fV;
  float newDelta = target - res;
  if (f > 0) {
    if (newDelta < 0) {
      fV = -fV;
      res = target + newDelta;
    }
  } else {
    if (newDelta > 0) {
      fV = -fV;
      res = target + newDelta;
    }
  }
  return res;
}
