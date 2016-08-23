#include <net/http/HTTP.h>

#include <iostream>
#include <sstream>

#include <io/ByteArrayOutputStream.h>
#include <io/DataOutputStream.h>
#include <io/InputStream.h>
#include <io/RestrictedInputStream.h>
#include <io/transcode/Base64OutputStream.h>
#include <util/ListIterator.h>

#include <net/http/ChunkedHTTPInputStream.h>

HTTP::HTTP(std::string _host, int _port)
    : host(_host), port(_port), authLine(0), s(0), fromServer(0), toServer(0),
      responce(0) {}

void HTTP::init() {
  if (s == 0) {
    s = new Socket(host, port);
    fromServer = &s->getInputStream();
    toServer = new DataOutputStream(&s->getOutputStream(), false);
  }
}

HTTP::~HTTP() {
  if (toServer != 0) {
    delete (toServer);
    toServer = 0;
  }

  if (s != 0) {
    delete (s);
    s = 0;
  }
  if (responce != 0) {
    delete (responce);
    responce = 0;
  }

  if (authLine != 0) {
    delete (authLine);
    authLine = 0;
  }
}

void HTTP::setKeepAlive() {
  std::string help = "Connection: Keep-Alive";
  parameters.push_back(help);
}

void HTTP::setFile(std::string _resName) { resName = _resName; }

void HTTP::setRange(long from, long to) {
  if ((from < 0) || (to < 0)) {
    throw(Exception("negative values illegal", __FILE__, __LINE__));
  }
  std::string help = "Range: bytes=";
  help += from;
  help += "-";
  if (to > 0) {
    help += to;
  }
  parameters.push_back(help);
}

void HTTP::setAuthorization(std::string userName, std::string passwd) {
  if (authLine != 0) {
    delete (authLine);
    authLine = 0;
  }
  ByteArrayOutputStream out(512);
  Base64OutputStream b64(&out, false);
  DataOutputStream dOut(&b64, false);

  unsigned int i;
  for (i = 0; i < userName.length(); i++) {
    b64.write(userName[i]);
  }
  b64.write(':');
  for (i = 0; i < passwd.length(); i++) {
    b64.write(passwd[i]);
  }
  b64.flush();

  std::ostringstream auth;
  auth << "Authorization: Basic ";

  char* help = (char*)(out.getData().getData());
  unsigned int size = out.getBytesWritten();
  for (i = 0; i < size; i++) {
    auth << (unsigned char)help[i];
  }

  authLine = new std::string(auth.str());
}

void HTTP::setReferer(std::string referer) {
  std::string help = "Referer: ";
  help += referer;
  parameters.push_back(help);
}

void HTTP::getHeader() {

  std::ostringstream help;
  // get feld
  help << "GET " << resName << " HTTP/1.1\r\n";

  // hostfeld
  help << "Host: " << host << "\r\n";

  // optionale authentifizierung
  if (authLine != 0) {
    help << *authLine << "\r\n";
  }

  // parameter
  ListIterator<std::string>* i = new ListIterator<std::string>(&parameters);
  while (i->hasNext() == true) {
    help << i->next() << "\r\n";
  }
  delete (i);

  // abschliessende leerzeile
  help << "\r\n";

  // zum server schicken
  std::string helpString(help.str());
  toServer->writeString(&helpString);
  toServer->flush();

  // antwort abwarten
  responce = new HTTPResponce(fromServer);
}

InputStream* HTTP::get() throw(Exception) {

  init();

  getHeader();

  // check answer either Content-Range, Content-Length,
  // or a chunked encoding must be given
  std::auto_ptr<std::string> value =
      std::auto_ptr<std::string>(responce->getValue("Content-Range"));
  if (value.get() != 0) {
    throw(Exception("HTTP::get - ContentRange not supported", __FILE__,
                    __LINE__));
    return 0;
  }

  value.reset(responce->getValue("Content-Length"));
  if (value.get() != 0) {
    long contentLength = Long::parseLong(*value);
    return new RestrictedInputStream(fromServer, contentLength, false);
  }

  value.reset(responce->getValue("Transfer-Encoding"));
  if (value.get() != 0) {
    return new ChunkedHTTPInputStream(fromServer);
  }

  return (fromServer);

  throw(Exception("HTTP::get - cannot handle data stream", __FILE__, __LINE__));

  /*

    std::string sizeV;
    if (i != header->end()) {
      std::string contentRange = i->second;
      int idx = contentRange.find('/');
      if (idx == std::string::npos) {
        std::string msg("Unexpected Format");
        msg += contentRange;
        Exception e(msg);
        throw(e);
      }
      sizeV = contentRange.substr(idx+1);
    } else {
      // look for content-length
      key = "Content-Length";
      i = header->find(key);
      if (i == header->end()) {
        throw(Exception("unerwartetes format"));
      }
      sizeV = i->second;
    }
    transferVolume = Long::parseLong(&sizeV);

  */
}
