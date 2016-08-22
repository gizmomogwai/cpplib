#include <io/file/FileOutputStream.h>

#include <lang/DataBuffer.h>
#include <io/file/File.h>
#include <sstream>

FileOutputStream::FileOutputStream(const char* fileName, 
                                   bool append) throw (IOException) {
  init(fileName, append);
}

FileOutputStream::FileOutputStream(const std::string fileName,
                                   bool append) throw (IOException) {
  init(fileName, append);
}

FileOutputStream::FileOutputStream(File* f,
                                   bool append) throw (IOException) {
  init(f->getPathName().c_str(), append);
}

FileOutputStream::~FileOutputStream() throw (IOException) {
  int res = fclose(out);
  if (res != 0) {
    std::string msg("FileOutputStream::~FileOutputStream - Fehler beim schliessen");
    IOException e(msg, __FILE__, __LINE__);
    throw e;
  }
}

void FileOutputStream::write(int b) throw (IOException) {
  unsigned char help = (unsigned char)(b & 0xff);
  int items = fwrite(&help, 1, 1, out);
  if (items != 1) {
    throw(IOException("FileOutputStream::write - could not write", 
                      __FILE__, __LINE__));
  }
}

void FileOutputStream::write(DataBuffer* b, int offset, int length) throw (IOException) {
  unsigned char* help = (unsigned char*)(b->getData(offset));
  int items = fwrite(help, length, 1, out);
  if (items != 1) {
    throw(IOException("FileOutputStream::write(DataBuffer - could not write",
                      __FILE__, __LINE__));
  }

}

void FileOutputStream::init(const std::string fileName, 
                            bool append) throw (IOException) {
  if (append == false) {
    out = fopen(fileName.c_str(), "wb");
  } else {
    out = fopen(fileName.c_str(), "a+b");
  }
  if (out == 0) {
    std::ostringstream h;
    h << "Konnte \"" << fileName << "\" nicht zum schreibeb oeffnen" << std::ends;
    IOException e(h.str(), __FILE__, __LINE__);
    throw(e);
  }
}

void FileOutputStream::flush() throw (IOException) {
  int res = fflush(out);
  if (res != 0) {
    throw(IOException("FileOutputStream::flush - could not fflush", 
                      __FILE__, __LINE__));
  }
}
