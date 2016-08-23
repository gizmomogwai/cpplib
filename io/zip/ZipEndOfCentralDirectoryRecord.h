#ifndef ZipEndIfCentralDirRecord_h_
#define ZipEndIfCentralDirRecord_h_

#include <string>
#include <sstream>
#include <io/file/File.h>
#include <io/file/FileInputStream.h>
#include <io/LittleEndianDataInputStream.h>

/** Klasse um das Ende eines ZipArchiveDirectories einzulesen.
 *
 * Es wird angenommen, dass kein Kommentar am Ende des ZipArchives
 * vorhanden ist.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-07-13, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2001/07/16 09:58:52 $
 *
 * @author cK, $Author: koestlin $
 */
class ZipEndOfCentralDirRecord {

  public:
    /** Liesst den Record ein.
     *
     * @param f File bleibt im Besitz des Callers.
     */
	  ZipEndOfCentralDirRecord(File* f) {
		  // assuming no .ZIP file comment at end of zip-file
		  FileInputStream fIn(f, f->getSize() - 22);
		  LittleEndianDataInputStream dIn(&fIn, false);

		  unsigned int signature = dIn.readInt();
		  if (signature != 0x06054b50) {
			  throw(Exception("cannot read zipdir", __FILE__, __LINE__));
		  }
		  idxOfThisDisk = dIn.readShort();
		  diskOfCentralDir = dIn.readShort();
		  nOfDirEntriesOnThisDisk = dIn.readShort();
		  nOfDirEntries = dIn.readShort();
		  sizeOfCentralDir = dIn.readInt();
		  diskRelativeOffset = dIn.readInt();
		  zipCommentLength = dIn.readShort();
	  }

    /** Raeumt auf. */
    virtual ~ZipEndOfCentralDirRecord() {
    }

    /** Erzeugt eine Stringrep.
     *
     * @return std::string String.
     */
	  std::string toString() {
		  std::ostringstream help;
      help << "EndOfCentralDirRecord :" << std::endl;
		  help << "idxOfThisDisks" << idxOfThisDisk << std::endl;
		  help << "diskOfCentralDir" << diskOfCentralDir << std::endl;
		  help << "nOfDirEntriesOnThisDisk" << nOfDirEntriesOnThisDisk <<
			  std::endl;
		  help << "nOfDirEntries" << nOfDirEntries << std::endl;
		  help << "sizeOfCentralDir" << sizeOfCentralDir << std::endl;
		  help << "diskRelativeOffset" << diskRelativeOffset << std::endl;
		  help << "zipCommentLength" << zipCommentLength << std::endl;
		  help << std::ends;
		  
		  std::string res(help.str());
		  return(res);
	  }
    
    /// Diskettenindex des enderecords.
	  unsigned short idxOfThisDisk;

    /// Diskettenindex des Directories.
	  unsigned short diskOfCentralDir;

    /// Anzahl von dateien auf dieser disk.
	  unsigned short nOfDirEntriesOnThisDisk;

    /// Gesamtzahl von Dateien.
	  unsigned short nOfDirEntries;

    /// groesse des directories.
	  unsigned int sizeOfCentralDir;

    /// offset des direktories auf seiner disk.
	  unsigned int diskRelativeOffset;

    /// laenge des zipcommentars.
	  unsigned short zipCommentLength;

};

#endif // EndIfCentralDirRecord_h_
