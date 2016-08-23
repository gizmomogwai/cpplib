#include <util/PropertyPrefs.h>

PropertyPrefs::PropertyPrefs(DataInputStream& in) { p.read(in); }

PropertyPrefs::~PropertyPrefs() {}
