#include <fltkwidgets/cf/IndexIterator.h>


CfIndexIterator::CfIndexIterator(const float pos) : fCount(21), fDelta(0), fStartIdx(lroundf(pos + 0.5f)) {
}
bool CfIndexIterator::hasNext() {
  return fCount > 0;
}
int CfIndexIterator::next() {
  int res = fStartIdx + fDelta;
  if (fDelta >= 0) {
    fDelta = -fDelta - 1;
  } else {
    fDelta = -fDelta;
  }
  --fCount;
  return res;
}
