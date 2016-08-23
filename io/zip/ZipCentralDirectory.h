#ifndef _ZipCentralDirectory_h_
#define _ZipCentralDirectory_h_

#include <string>
#include <sstream>
#include <list>

#include <io/file/File.h>
#include <io/file/FileNotFoundException.h>
#include <io/file/FileInputStream.h>
#include <io/LittleEndianDataInputStream.h>

#include <io/zip/ZipFileHeader.h>
#include <io/zip/ZipEndOfCentralDirectoryRecord.h>
#include <util/ListIterator.h>

/** Repraesentiert den Directoryeintrag des ZipFiles.
 *
 * Liesst zunaechst den EndOfCentralDirRecord ein.
 * Daufhin werden alle Files im Zip-File eingelesen.
 * Evtl. ist das dumm, da das sehr viele Dateien sein 
 * koennen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-07-13, cK, Created.
 * </ul>
 *
 * @author cK, $Author: koestlin $
 *
 * @version $Revision: 1.1 $ $Date: 2001/07/16 09:58:52 $
 */
class ZipCentralDirectory {
  public:
    /** Erzeugt das Directory fuer ein Zip-File.
     *
     * @param f Das ZipFile bleibt im Besitz des Callers.
     */
  	ZipCentralDirectory(File* f) {
		  ZipEndOfCentralDirRecord end(f);

      if (end.diskOfCentralDir != 0) {
        throw(Exception("multidisk", __FILE__, __LINE__));
      }
  
      FileInputStream dirInputStream(f, end.diskRelativeOffset);
      LittleEndianDataInputStream dirDIn(&dirInputStream, false);

      for (int i=0; i<end.nOfDirEntries; i++) {
        files.push_back(new ZipFileHeader(&dirDIn));
      }
  	}

    /** Raeumt auf. */
    virtual ~ZipCentralDirectory() {
      ListIterator<ZipFileHeader*> i(&files);
      while (i.hasNext() == true) {
        delete(i.next());
      }
    }

    /** Sucht im Directory nach einem File.
     *
     * @param fileName Name des Files.
     *
     * @return FileHeader* Headerinfos des Files. Bleibt im 
     *         Besitz des Directorys.
     */
    ZipFileHeader* findFile(std::string fileName) {
  
      ListIterator<ZipFileHeader*> i(&files);
      while (i.hasNext() == true) {
        ZipFileHeader* header = i.next();
        if (fileName == *(header->fileName)) {
          return(header);
        }
      }
      throw(FileNotFoundException(fileName, __FILE__, __LINE__));
    }


  private:
    /** Liste mit den Fileheadern. */
    std::list<ZipFileHeader*> files;
};

#endif // _ZipCentralDirectory_h_
