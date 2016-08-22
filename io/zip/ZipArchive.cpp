#include <io/zip/ZipArchive.h>

#include <io/file/File.h>
#include <io/zip/ZipCentralDirectory.h>
#include <io/zip/ZipEntry.h>


ZipArchive::ZipArchive(File* f)  : file(new File(f)) {
	dir = new ZipCentralDirectory(file);
}


ZipArchive::~ZipArchive() {
	delete(dir);
	delete(file);
}

InputStream* ZipArchive::getStream(std::string fileName, 
																	 std::string* passwd) {
	ZipFileHeader* found = dir->findFile(fileName);
	
	ZipEntry zipEntry(found, file);
	return(zipEntry.getData(passwd));
}
