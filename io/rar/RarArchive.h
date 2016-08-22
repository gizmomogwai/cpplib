#ifndef _RarArchive_h_
#define _RarArchive_h_

#include <io/IoApi.h>

#include <windowsinclude.h>

#include <unrar.h>

#include <string>
#include <io/file/File.h>
class InputStream;

/** Sollte mal ein RarArchive werden.
 *
 * Problem ist, dass man keinen wahlfreien zugriff auf einzelne dateien in
 * dem rar-archive hat. Insofern ist das uninteressant.
 */
class IO_API RarArchive {

public:

	RarArchive(File* f);

	virtual ~RarArchive();

	InputStream* getStream(std::string fileName, std::string* passwd=0);

private:
	File archive;

  HANDLE rarArchive;

};


#endif // _RarArchive_h_
