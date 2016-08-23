#include <net/http/HTTPResponce.h>

#include <iostream>
#include <lang/Exception.h>
#include <lang/Integer.h>
#include <lang/Long.h>
#include <sstream>
#include <string>

FirstHTTPLine::FirstHTTPLine(DataInputStream* in) throw(Exception) {
  line = in->readLine();
  if (line.get() != 0) {
    if (line->find("HTTP/1.1") == std::string::npos) {
      if (line->find("HTTP/1.0") == std::string::npos) {
        throw Exception("only http/1.1 supported, but found: " + (*line),
                        __FILE__, __LINE__);
      } else {
        std::cout << "WARNING - Only http/1.0" << std::endl;
      }
    }
    std::string res = line->substr(9, 3);
    result = Integer::parseInt(res);

    if (isOK() == false) {

      std::ostringstream help;
      help << "FirstHTTPLine::FirstHTTPLine() - " << *line << std::ends;
      std::string theMessage = help.str();
      throw Exception(theMessage, __FILE__, __LINE__);
    }
  }
}

FirstHTTPLine::~FirstHTTPLine() {}

std::string FirstHTTPLine::getAnswer() { return *line; }

bool FirstHTTPLine::isOK() {
  if ((result == 200) || (result == 206)) {
    return (true);
  } else {
    return (false);
  }
}

HTTPResponce::HTTPResponce(InputStream* _in) throw(Exception)
    : in(0), header(0), transferVolume(0) {

  in = new DataInputStream(_in, false);

  try {

    FirstHTTPLine firstLine(in);

  } catch (Exception& e) {

    delete (in);
    throw(e);
  }

  readHeader();
}

HTTPResponce::~HTTPResponce() {

  if (in != 0) {
    delete (in);
    in = 0;
  }
  if (header != 0) {
    delete (header);
    header = 0;
  }
}

void HTTPResponce::readHeader() throw(Exception) {

  header = new std::map<std::string, std::string>();
  std::auto_ptr<std::string> line(in->readLine());

  while ((line.get() != 0) && (line->size() != 0)) {
    int idx = line->find(':');
    std::string aKey = line->substr(0, idx);
    std::string aValue = line->substr(idx + 2);

    header->insert(std::make_pair(aKey, aValue));

    line = in->readLine();
  }
}

std::string* HTTPResponce::getValue(std::string key) {

  std::map<std::string, std::string>::iterator i = header->find(key);
  if (i == header->end())
    return (0);

  std::string* res = new std::string(i->second);
  return (res);
}
