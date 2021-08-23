#include <util/Properties.h>

#include <iostream>
#include <sstream>
#include <util/StringTokenizer.h>

Properties::Properties() {}

Properties::~Properties() {}

void Properties::read(DataInputStream& in) {
  auto line = in.readLine();
  while (line.get() != 0) {

    if (line->length() > 0) {
      if (line->at(0) != '#') {
        StringTokenizer tokens(*line, "=");
        auto key = tokens.next();
        auto value = tokens.next();

        if ((key.get() != 0) && (value.get() != 0)) {
          setProperty(*key, *value);
        }
      }
    }
    line = in.readLine();
  }
}

void Properties::write(DataOutputStream& out) {
  std::map<std::string, std::string>::iterator i = theMap.begin();
  while (i != theMap.end()) {
    std::string h(i->first);
    out.writeString(&h);
    out.write('=');
    h = std::string(i->second);
    out.writeString(&h);
    out.writeLine();
    i++;
  }
}

std::string
Properties::getProperty(const std::string& key) throw(NoSuchElementException) {
  std::map<std::string, std::string>::iterator found = theMap.find(key);
  if (found == theMap.end()) {
    NoSuchElementException e(std::string("could not find property: ") + key);
    throw e;
  } else {
    return found->second;
  }
}

std::string Properties::getProperty(const std::string& key,
                                    const std::string& defaultValue) {
  std::map<std::string, std::string>::iterator found = theMap.find(key);
  if (found == theMap.end()) {
    return defaultValue;
  } else {
    return found->second;
  }
}

void Properties::setProperty(const std::string& key, const std::string& value) {
  std::map<std::string, std::string>::iterator found = theMap.find(key);

  if (found != theMap.end()) {
    found->second = value;
  } else {
    theMap.insert(std::make_pair(key, value));
  }
}

std::string Properties::toString() {
  std::ostringstream help;
  help << "Properties:" << std::endl;
  std::map<std::string, std::string>::iterator i = theMap.begin();
  while (i != theMap.end()) {
    help << i->first << "=" << i->second << std::endl;
    i++;
  }
  help << std::ends;

  std::string res(help.str());

  return (res);
}
