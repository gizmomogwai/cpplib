#ifndef Approacher_h_
#define Approacher_h_


class Approacher {
 public:
  virtual ~Approacher() {}
  virtual float approach(const float current, const float target) = 0;
};

class LinearApproacher : public Approacher {
 public:
  float approach(const float current, const float target);
};

class SpringApproacher : public Approacher {
 public:
  SpringApproacher();
  float approach(const float current, const float target);
 private:
  float fV;

};

class BouncingApproacher : public Approacher {
 public:
  BouncingApproacher();
  float approach(const float current, const float target);
 private:
  float fV;
};

#endif
