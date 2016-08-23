#include <util/Preferences.h>

std::string
Preferences::getString(const std::string& key,
                       const std::string& v) throw(NoSuchElementException) {
  try {
    return (getString(key));
  } catch (NoSuchElementException) {
    return (v);
  }
}
