#include <util/StringTokenizer.h>

#include <util/StringTools.h>

StringTokenizer::StringTokenizer(std::string _source, std::string _delimiters)
    : source(_source), delimiters(_delimiters) {

  start = source.begin();
}

StringTokenizer::~StringTokenizer() {}

bool StringTokenizer::isDelimiter(char v) {
  return (StringTools::contains(&delimiters, v));
}

std::auto_ptr<std::string> StringTokenizer::rest() {
  end = source.end();
  return std::auto_ptr<std::string>(new std::string(start, end));
}

std::auto_ptr<std::string> StringTokenizer::next() {
  // ueberspringe fuehrende delimiters
  while ((start != source.end()) && (isDelimiter(*start) == true)) {
    start++;
  }
  end = start;

  int found = 0;
  // laufe bis zum ersten delimiter
  while ((end != source.end()) && (isDelimiter(*end) == false)) {
    found++;
    end++;
  }

  if (found == 0) {
    return std::auto_ptr<std::string>(0);
  }

  std::auto_ptr<std::string> res(new std::string(start, end));
  start = end;

  return res;
}
