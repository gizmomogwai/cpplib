#include <lang/Exception.h>

#include <iostream>

Exception::Exception() {}

Exception::Exception(const char* m) { msg = std::string(m); }

Exception::Exception(const std::string _msg) { msg = std::string(_msg); }

Exception::Exception(const std::string _msg, const std::string fileName,
                     const int lineNr) {
  std::ostringstream help;
  help << _msg << "  (" << fileName << " : " << lineNr << ")" << std::ends;
  msg = help.str();
}

Exception::Exception(std::ostringstream* _msg, const std::string fileName,
                     const int lineNr) {
  std::ostringstream help;
  help << *_msg << "  (" << fileName << " : " << lineNr << ")" << std::ends;
  msg = help.str();
}

std::string Exception::getMessage() { return (msg); }
