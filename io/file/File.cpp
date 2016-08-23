#include <io/file/File.h>

#include <io/IOTools.h>

#include <sys/stat.h>

#if defined(WIN32)
  #include <sys/utime.h>
  #include <io/file/Filedirent.h>
  
  #include <direct.h> // for getcwd
  #include <stdlib.h>// for MAX_PATH
  const int FILE_MAX_PATH_LENGTH = _MAX_PATH;
#elif defined(LINUX) || defined(OSX)
  #include <sys/param.h>
  const int FILE_MAX_PATH_LENGTH = MAXPATHLEN;
  #include <utime.h>
  #include <sys/types.h>
  #include <dirent.h>
#else
  #error "problems ahead captain"
#endif

#include <sstream>
#include <algorithm>
#include <iterator>

#include <lang/CleanUpObject.h>
#include <util/StringTokenizer.h>

File::File(std::string _pathName) : pathName(_pathName) {
  unifyName();
}

File::File(File* f) : pathName(f->pathName) {
  unifyName();
}

File::File(const File& f) : pathName(f.pathName) {
  unifyName();
}

File::File(File* base, std::string childName) {
  if (base == 0) {
  	throw Exception("base must not be 0");
  }
  std::ostringstream h;
  
  if (childName == "..") {
    
  }  
  std::string baseName = base->getPathName();
  h << baseName;
  if (baseName.at(baseName.length() - 1) != '(') {
      h << '/';
  }
  h << childName;
  pathName = h.str();
	
  unifyName();
}

File* File::getParent() {
  if (isDirectory() == true) {
    return(new File(chopSlashes(2)));
  } else {
    return(new File(chopSlashes(1)));
  }
}

std::string File::chopSlashes(unsigned int i) {
  std::string::reverse_iterator reverse = pathName.rbegin();
  int position = pathName.length();
  while ((reverse != pathName.rend()) && (i > 0)) {
    char help = *reverse;
    if ((help == '/') || (help == '\\')) {
      i--;
    }
    reverse++;
    position--;
  }
  std::string res = pathName.substr(0, position);
  return res;
}

long File::getSize() throw (IOException) {
  FILE* file = fopen(pathName.c_str(), "rb");
  if (file == 0) {
    std::ostringstream h;
    h << "File \"" << pathName << "\" not found" << std::ends;
    IOException e(h.str(), __FILE__, __LINE__);
    throw(e);
  }
  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  fclose(file);
  return(fileSize);
}

void File::remove() throw (IOException) {
  int res = ::remove(pathName.c_str());
  if (res != 0) {
    std::ostringstream h;
    h << "File \"" << pathName << "\" konnte nicht geloescht werden." 
    << std::ends;
    IOException e(h.str(), __FILE__, __LINE__);
    throw(e);
  } 
}

void File::rename(File* target) throw (IOException) {
  int res = ::rename(pathName.c_str(), target->pathName.c_str());
  if (res != 0) {
    std::ostringstream h;
    h << "File \"" << pathName << "\" konnte nicht in \"" 
    << target->pathName << "\" umbenannt werden.";
    IOException e(h.str(), __FILE__, __LINE__);
    throw(e);
  }
}

void File::copy(File* target) throw (IOException) {
  FileInputStream fIn(this);
  FileOutputStream fOut(target);
  
  IOTools::copy(&fIn, &fOut, 2048);
}



bool File::isDirectory() const {
  DIR* test = opendir(pathName.c_str());
  bool res = false;
  if (test != 0) {
    res = true;
    closedir(test);
  }
  return res;
}

bool File::exists() {
  try {
    FileInputStream in(this);
    return true;
  } catch (Exception& e) {
    return false;        
  }
}

FileList* File::list() {
  DIR* d = opendir(pathName.c_str());
  FileList* res = new FileList();
  if (d != 0) {
    
    struct dirent* entry = readdir(d);
    while (entry != 0) {
      if (((std::string(".") == entry->d_name) || (std::string("..") == entry->d_name)) == false) {
        File* f = new File(this, entry->d_name);
        res->push_back(f);
      }
      entry = readdir(d);
      
    }
    closedir(d);
  } 
  return res ;
}

void File::unifyName() {
  std::replace(pathName.begin(), pathName.end(), '\\', '/');
  
  std::vector<std::string> paths;
  
  StringTokenizer tokens(pathName, "/");
  std::auto_ptr<std::string> token = tokens.next();
  while (token.get() != 0) {
    if (((*token) != "..") || (paths.empty() || (paths.back() == ".."))) {   
      paths.push_back(*token);
    } else {
      paths.pop_back();
    }
    
    token = tokens.next();
  }
  
  std::ostringstream h;
  std::copy( paths.begin(), paths.end(), ostream_iterator<std::string>(h, "/") );
  
  if (pathName.find("/") == 0) {
    pathName = "/";
  } else {
    pathName = "";
  }
  pathName += h.str();
  if (pathName.size() > 1) {
    pathName = pathName.substr(0, pathName.size()-1);
  }
}

std::string File::getFileName() {
	std::size_t pos = pathName.find_last_of("/");
	if (pos == std::string::npos) {
		return "";
	} else {
		return pathName.substr(pos+1, pathName.length() - pos - 1);
	}
}

bool File::mkdir() {
	#ifdef WIN32
	return CreateDirectory(pathName.c_str(), 0);
	#endif
	
  #if defined(LINUX) || defined(OSX)
	return 0 == ::mkdir(pathName.c_str(), S_IRWXU);
	#endif
}

void File::setDates(Date* accessDate, Date* modificationDate) {
	CleanUpObject<Date> modificationDateToSet;
	if (modificationDate == 0) {
		modificationDateToSet.setCleanUp(getModificationDate());
	} else {
		modificationDateToSet.setCleanUp(new Date(modificationDate));
	}
	
	CleanUpObject<Date> accessDateToSet;
	if (accessDate == 0) {
		accessDateToSet.setCleanUp(getLastAccessDate());
	} else {
		accessDateToSet.setCleanUp(new Date(accessDate));
	}
  
	struct utimbuf utimeBuf;
        utimeBuf.actime = accessDateToSet->getTimeT();
	utimeBuf.modtime = modificationDateToSet->getTimeT();
	
	::utime(getPathName().c_str(), &utimeBuf);
}

Date* File::getLastAccessDate() {
	struct stat fileStats;
	stat(getPathName().c_str(), &fileStats);
	return new Date(&fileStats.st_atime);
}

Date* File::getModificationDate() {
	struct stat fileStats;
	stat(getPathName().c_str(), &fileStats);
	return new Date(&fileStats.st_mtime);
	
	#ifdef WIN32STUFF
  HANDLE fileHandle;
  fileHandle = ::CreateFile(TEXT(getPathName().c_str()), 
    GENERIC_READ, 
    FILE_SHARE_READ,
    0, 
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL,
    0);
  assert(fileHandle != INVALID_HANDLE_VALUE);
  
  FILETIME creationFileTime;
  FILETIME lastAccessFileTime;
  FILETIME lastWriteFileTime;
  BOOL res = ::GetFileTime(fileHandle, 
    &creationFileTime, 
    &lastAccessFileTime, 
    &lastWriteFileTime);
  ::CloseHandle(fileHandle);
  
  assert(res);
  
  SYSTEMTIME stNotLocal;
  ::FileTimeToSystemTime(&lastWriteFileTime, &stNotLocal);
  
  TIME_ZONE_INFORMATION timeZone;
  ::GetTimeZoneInformation(&timeZone);
  
  SYSTEMTIME st;
  ::SystemTimeToTzSpecificLocalTime(&timeZone, &stNotLocal, &st);
	
  return new Date(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	#endif // WIN32STUFF
}


File File::getCwd() {
  char cwd[FILE_MAX_PATH_LENGTH];
  ::getcwd(cwd, FILE_MAX_PATH_LENGTH);
  File res(cwd);
  return res;  
}
