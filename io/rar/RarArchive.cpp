#include <io/rar/RarArchive.h>

RarArchive::RarArchive(File* f) : archive(f) {
  struct RAROpenArchiveData openParam;
  openParam.ArcName = (char*)archive.getPathName().c_str();
  openParam.OpenMode = RAR_OM_EXTRACT;
  openParam.CmtBuf = NULL;
  openParam.CmtBufSize = 0;

  rarArchive = ::RAROpenArchive(&openParam);
  if ((rarArchive == NULL) ||
      (openParam.OpenResult != 0)) {
    throw(IOException("probleme bei rar-open"));
  }
}

RarArchive::~RarArchive() {
  if (rarArchive != NULL) {
    int res = ::RARCloseArchive(rarArchive);
    if (res != 0) {
      throw(IOException("Problems closing rar"));
    }
  }
}

InputStream* getStream(std::string fileName, std::string* passwd) {

  
  return(0);
}
