#ifndef Animator_h_
#define Animator_h_

#include <lang/Mutex.h>
class Approacher;

class Animatable : public Mutex {
 public:
  Animatable();
  virtual ~Animatable() {}
  virtual void update() = 0;
  float getTargetPosition();
  void setTargetPosition(const float pos);
  float getCurrentPosition();
  void setCurrentPosition(const float pos);
  bool hasChanged();
  void setChanged(const bool changed);
 private:
  float fTargetPos;
  float fCurrentPos;
  bool fChanged;
};

class Animator {
 public:
  Animator(Approacher& approacher, Animatable& animatable);
  ~Animator();
  void animate();
 private:
  static void timer(void* userdata);
  Approacher& fApproacher;
  Animatable& fAnimatable;
  static const float timeout;
};



#endif


