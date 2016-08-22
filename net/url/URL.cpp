#include <net/url/URL.h>

#include <net/url/URLInputStream.h>

InputStream* URL::openStream() {
  return new URLInputStream(this);
}
