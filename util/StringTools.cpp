#include <util/StringTools.h>

std::string* StringTools::trim(std::string* src, std::string* what) {

  std::string::iterator start = src->begin();
  
  while ((start != src->end()) && (contains(what, *start) == true)) {
    start++;
  }
  
  std::string::iterator end = start;
  std::string::iterator help = start;
  while (help != src->end()) {
    if (contains(what, *help) == false) {
      end = help;
    }
    help++;
  }
  
  if (end != src->end()) {
    end++;
  }

  return(new std::string(start, end));
}


bool StringTools::contains(std::string* src, char v) {
  std::string::size_type pos = src->find(v);
  if (pos == std::string::npos) {
    return false;
  }
  return true;
}
