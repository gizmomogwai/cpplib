#ifndef _URL_h_
#define _URL_h_

#include <windowsinclude.h>

#include <string>
#include <io/InputStream.h>

class URL {
 public:
 URL(std::string _url) : url(_url) {
  }

  virtual ~URL() {
  }

  InputStream* openStream();

  std::string toString() {
    return(url);
  }

 private:
  std::string url;

};

#endif // _URL_h_
