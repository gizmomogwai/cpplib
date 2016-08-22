#include <io/file/FileList.h>

#include <util/ListIterator.h>
#include <io/file/File.h>

FileList::~FileList() {
  VectorIterator<File*> i(this);
  while (i.hasNext() == true) {
    File* current = i.next();
    delete current;
  }
}

FileList* FileList::duplicate() {
  FileList* res = new FileList();
  VectorIterator<File*> i(this);
  while (i.hasNext()) {
    res->push_back(new File(i.next()));
  }
  return res;
}
