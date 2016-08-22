#ifndef IndexIterator_h_
#define IndexIterator_h_

#include <util/Iterator.h>
#include <math.h>

class IndexIterator : public Iterator<int> {
};

class CfIndexIterator : public IndexIterator {
 public:
  CfIndexIterator(const float pos);
  bool hasNext();
  int next();
 private:
  unsigned int fCount;
  int fDelta;
  int fStartIdx;
};

template <unsigned int COUNT> 
class ZeroEndMinusOneIndexIterator : public IndexIterator {
 public:
 ZeroEndMinusOneIndexIterator(const float pos) : fCount(COUNT), fDelta(0), fStartIdx(lroundf(pos + 0.5f)) {
  }

  bool hasNext() {
    return fCount > 0;
  }

  int next() {
    int res = 0;
    if (fCount == 1) {
      res = fStartIdx - 1;
    } else {
      res = fStartIdx + fDelta++;
    }
    --fCount;
    return res;
  }

 private:
  unsigned int fCount;
  int fDelta;
  int fStartIdx;
};

class IndexIteratorFactory {
 public:
  virtual ~IndexIteratorFactory() {}
  virtual IndexIterator* get(const float pos) = 0;

};

template <typename T>
class IndexIteratorFactoryFor : public IndexIteratorFactory {
 public:
  IndexIterator* get(const float pos) {
    return new T(pos);
  }
};

#endif
