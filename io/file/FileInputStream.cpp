#include <io/file/FileInputStream.h>

//#include <lang/DataBuffer.h>
#include <io/file/File.h>
#include <string>
#include <sstream>
#include <iostream>

FileInputStream::FileInputStream(const char* fileName, const int offset) 
  throw (IOException) {
  
  init(fileName, offset);
}

FileInputStream::FileInputStream(std::string fileName, const int offset) 
  throw (IOException) {
  
  init(fileName.c_str(), offset);
}

FileInputStream::FileInputStream(File* f, const int offset) 
  throw (IOException) {
  
  init(f->getPathName().c_str(), offset);
}

FileInputStream::FileInputStream(FILE* _in) throw (IOException)
  : pleaseClose(false), in(_in) {
}

void FileInputStream::init(const char* fileName, const int offset) throw (IOException) {
  in = 0;
  in = fopen(fileName, "rb");
  if (in == 0) {
    std::ostringstream help;
    help << "File " << fileName << " not found" << std::ends;
    std::string errorMsg = help.str();
    throw(IOException(errorMsg, __FILE__, __LINE__));
  } else {
    pleaseClose = true;
    if (offset != 0) {
      int res = fseek(in, offset, SEEK_SET);
      if (res != 0) {
        throw(IOException("FileInputStream::init - fseek failed", __FILE__, __LINE__));
      }
    }
  }
}

int FileInputStream::read() throw (IOException) {
  unsigned char v = 0;
  int res = fread(&v, 1, 1, in);
  if (res == 0) {
    return(-1);
  }
  return((int)v);
}

int FileInputStream::read(DataBuffer& b, int offset, int length) 
  throw (IOException) {

  unsigned char* help = (unsigned char*)(b.getData(offset));
  
  size_t res = fread(help, 1, length, in);
  if (res == 0) {
    return -1;
  }
  return res;
}


FileInputStream::~FileInputStream() {
  if (pleaseClose == true) {
    if (in != 0) {
      fclose(in);
    }
  }
}
