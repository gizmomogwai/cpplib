#include <io/zip/ZipFileHeader.h>

#include <lang/Exception.h>

#include <lang/DataBuffer.h>

ZipFileHeader::ZipFileHeader(DataInputStream* dIn) 
	: fileName(0), extraField(0), fileComment(0) {

  unsigned int centralFileHeaderSignature = dIn->readInt();
  if (centralFileHeaderSignature != 0x02014b50) {
    throw(Exception("no file header signature", __FILE__, __LINE__));
  }
  madeBy = dIn->readShort();
  needed2Extract = dIn->readShort();
  generalPurpose = dIn->readShort();
  compressionMethod = dIn->readShort();
  lastModTime = dIn->readShort();
  lastModDate = dIn->readShort();
  crc32 = dIn->readInt();
  compressedSize = dIn->readInt();
  uncompressedSize = dIn->readInt();
  fileNameLength = dIn->readShort();
  extraFieldLength = dIn->readShort();
  fileCommentLength = dIn->readShort();
  disk = dIn->readShort();
  if (disk != 0) {
    throw(Exception("multidisk", __FILE__, __LINE__));
  }
  internalFileAttributes = dIn->readShort();
  externalFileAttributes = dIn->readInt();
  offsetOfLocalHeader = dIn->readInt();
  readFileName(dIn);
  readExtraField(dIn);
  readFileComment(dIn);
}


ZipFileHeader::~ZipFileHeader() {
  if (fileName != 0) {
    delete(fileName);
    fileName = 0;
  }
  if (extraField != 0) {
    delete(extraField);
    extraField = 0;
  }
  if (fileComment != 0) {
    delete(fileComment);
    fileComment = 0;
  }
}


std::string* ZipFileHeader::readString(int length, DataInputStream* dIn) {
  std::string* res = 0;
  if (length != 0) {
    char* help = new char[length + 1];
    help[length] = 0;
    DataBuffer buffer(help, length + 1, false);
    dIn->read(buffer, 0, length);
    res = new std::string(help);
    delete[](help);
  }
  return(res);
}
