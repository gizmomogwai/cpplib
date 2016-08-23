#pragma once

#include <string>
#include <lang/CleanUpArray.h>

class Strings {
  public:
    static std::string toLower(std::string &s) {
      char* buf = new char[s.length()];
      CleanUpArray<char> bufCleaner(buf);
      
      s.copy(buf, s.length());
      for(unsigned int i = 0; i < s.length(); i++) {
        buf[i] = tolower(buf[i]);
      }
      
      return std::string(buf, s.length());
    }
  
};

