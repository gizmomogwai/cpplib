#include <fltkwidgets/Animator.h>

#include <fltkwidgets/Approacher.h>
#include <fltk/run.h>

Animatable::Animatable() : fTargetPos(0.0f), fCurrentPos(0.0f), fChanged(false) {
}

float Animatable::getTargetPosition() {
  AutoMutex lock(this);
  return fTargetPos;
}

void Animatable::setTargetPosition(const float targetPos) {
  AutoMutex lock(this);
  fTargetPos = targetPos;
}

float Animatable::getCurrentPosition() {
  AutoMutex lock(this);
  return fCurrentPos;
}

void Animatable::setCurrentPosition(const float currentPos) {
  AutoMutex lock(this);
  fCurrentPos = currentPos;
}

bool Animatable::hasChanged() {
  AutoMutex lock(this);
  return fChanged;
}
void Animatable::setChanged(const bool changed) {
  AutoMutex lock(this);
  fChanged = changed;
}

const float Animator::timeout = 1.0f / 30.0f;

Animator::Animator(Approacher& approacher, Animatable& animatable) : fApproacher(approacher), fAnimatable(animatable) {
  fltk::add_timeout(Animator::timeout, timer, static_cast<void*>(this)); 
}

Animator::~Animator() {
  fltk::remove_timeout(timer, (void*)this);
}

void Animator::timer(void* userdata) {
  Animator* animator = static_cast<Animator*>(userdata);
  animator->animate();
  fltk::repeat_timeout(Animator::timeout, timer, userdata); 
}

void Animator::animate() { 
  AutoMutex lock(&fAnimatable);
  
  if (fAnimatable.hasChanged()) {
    fAnimatable.setChanged(false);
    fAnimatable.setCurrentPosition(fAnimatable.getTargetPosition());
    fAnimatable.update();
  } else {
    const float current = fAnimatable.getCurrentPosition();
    const float target = fAnimatable.getTargetPosition();
    const float newPos = fApproacher.approach(current, target);
    if (newPos != current) {
      fAnimatable.setCurrentPosition(newPos);
      fAnimatable.update();
    }
  }
}
