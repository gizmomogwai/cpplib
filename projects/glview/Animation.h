#pragma once

#include <list>
#include <functional>
#include <sg/visitors/CustomData.h>

class Callback {
public:
  virtual ~Callback() {}
};

class Animation : public CustomData {
public:
  Animation(const std::function<void (void)> _done) : done(_done) {}
  virtual ~Animation() {}
  /**
   * @return true if animation is not yet finished
   */
  virtual bool step() = 0;
  virtual std::string toString() const {
    return "Animation";
  }
  const std::function<void (void)> done;
};

/**
 * An animation group can be used to attach a callback to a list of
 * animations that is called if all of them are done.
 */
class AnimationGroup : public Animation {
public:
  AnimationGroup(const std::function<void (void)> _done) : Animation(_done) {
  }
  ~AnimationGroup() {
    std::cout << "TODO: delete all animations in animation group\n";
  }
  void add(Animation* animation) {
    todo.push_back(animation);
  }
  bool step() {
    auto i = todo.begin();
    while (i != todo.end()) {
      auto finished = (*i)->step();
      if (finished) {
        auto done = *i;
        i = todo.erase(i);
        done->done();
      }
      i++;
    }
    return todo.size() == 0;
  }
  std::string toString() const {
    return "AnimationGroup";
  }

private:
  std::list<Animation*> todo;
};

class Animations {
public:

  void run(Animation* animation) {
    std::cout << "run animation " << animation->toString() << std::endl;
    (inAnimation ? newAnimations : animations).push_back(animation);
  }

  void animate() {
    newAnimations.clear();
    inAnimation = true;
    auto i = animations.begin();
    while (i != animations.end()) {
      bool animationFinished = (*i)->step();
      if (animationFinished) {
        auto done = *i;
        i = animations.erase(i);
        done->done();
      }
      i++;
    }
    inAnimation = false;
    animations.insert(animations.end(), newAnimations.begin(), newAnimations.end());
  }

  size_t size() const {
    return animations.size();
  }

  const std::string toString() const {
    return "Animations";
  }

private:
  std::list<Animation*> animations;
  bool inAnimation = false;
  std::list<Animation*> newAnimations;
};
