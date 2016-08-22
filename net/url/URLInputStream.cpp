#include <net/url/URLInputStream.h>

#include <lang/Exception.h>
#include <net/url/URL.h>
#include <assert.h>
#include <lang/DataBuffer.h>

#ifdef WIN32

URLInputStream::URLInputStream(URL* url) {
  internet = InternetOpen("Test", 
                          INTERNET_OPEN_TYPE_PRECONFIG, 
                          NULL, 
                          NULL, 
                          0);
  if (internet == NULL) {
    throw(Exception("URLInputStream::URLInputStream - could not open Internet", __FILE__, __LINE__));
  }

  connection = InternetOpenUrl(internet, 
                               url->toString().c_str(), 
                               NULL, 0, 
                               0, 
                               0);
  if (connection == NULL) {
    throw(Exception("URLInputStream::URLInputStream - could not open connection", __FILE__, __LINE__));
  }
}

URLInputStream::~URLInputStream() {
  if (connection != NULL) {
    BOOL bRes = InternetCloseHandle(connection);
    assert(bRes != FALSE);
    connection = 0;
  }
  if (internet != NULL) {
    BOOL bRes = InternetCloseHandle(internet);
    assert(bRes != FALSE);
    internet = 0;
  }
}

int URLInputStream::read() throw (IOException) {
  int res;
  unsigned long red;
  BOOL bRes = InternetReadFile(connection, &res, 1, &red);
  if (red == 0) {
    res = -1;
  }
  if (bRes == FALSE) {
    res = -1;
  }
  return(res);
}

int URLInputStream::read(DataBuffer* buffer, int offset, int length) 
  throw (IOException) {

  unsigned long res;
  BOOL bRes = InternetReadFile(connection, buffer->getData(offset), length, &res);
  if (res == 0) {
    return(-1);
  }
  if (bRes == FALSE) {
    return(-1);
  }
  return(res);
}

#endif
