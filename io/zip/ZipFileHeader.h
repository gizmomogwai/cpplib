#ifndef _ZipFileHeader_h_
#define _ZipFileHeader_h_

#include <io/IoApi.h>

#include <string>

#include <io/DataInputStream.h>

/** Header eines ZipEntrys im CentralDirectory.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-07-13, cK, Created.
 *   <li> 2001-09-10, cK, Includes verbessert, ins cpp file bewegt.
 * </ul>
 *
 * @version $Revision: 1.2 $ $Date: 2001/09/13 13:11:10 $
 *
 * @author cK, $Author: koestlin $
 */
class IO_API ZipFileHeader {
  public:
    /** Directoryeintrag eines ZipEintrages.
     *
     * @param dIn Daten fuer den Eintrag.
     */
    ZipFileHeader(DataInputStream* dIn);

    /** Raeumt auf. */
    virtual ~ZipFileHeader();

    /// hersteller des Zips.
    unsigned short madeBy;

    /// version die benoetigt wird um zu enpacken.
    unsigned short needed2Extract;

    /** zusatzparameter fuer die compression und 
     * location der crcs und encryption.
     */
    unsigned short generalPurpose;

    /// compressionsmethode (nur uncompressed und deflate implementiert).
    unsigned short compressionMethod;

    /// time im dos-format.
    unsigned short lastModTime;

    /// datum im dos-format.
    unsigned short lastModDate;

    /// crc des eintrags.
    unsigned int crc32;

    /// komprimierte groesse.
    unsigned int compressedSize;

    /// unkomprimierte groesse.
    unsigned int uncompressedSize;

    /// laenge des Filenamens.
    unsigned short fileNameLength;

    /// laenge der zusatzdaten.
    unsigned short extraFieldLength;

    /// laenge des filecommentars.
    unsigned short fileCommentLength;

    /// disk auf der der eintrag zu finden ist.
    unsigned short disk;

    /// unterscheidung ascii binary.
    unsigned short internalFileAttributes;

    /// evtl. directory-flag.
    unsigned int externalFileAttributes;

    /// offset von der disk zum localfileheader.
    unsigned int offsetOfLocalHeader;

    /// optionaler filename
    std::string* fileName;

    /// hier kann einiges drinstehen.
    std::string* extraField;

    /// filecommentar
    std::string* fileComment;

  private:
    /** Liesst einen String einer bestimmten Laenge vom DataInputStream.
     *
     * @param length Laenge des String.
     * @param dIn DataInputStream.
     *
     * @return std::string* string oder 0.
     */
    std::string* readString(int length, DataInputStream* dIn);

    /** Liesst den Filenamen aus den daten aus.
     *
     * @param dIn Daten zum Filenamen.
     */
    void readFileName(DataInputStream* dIn) {
      fileName = readString(fileNameLength, dIn);
    }

    /** Liesst die Extrafielddaten aus den Daten aus.
     *
     * @param dIn Daten.
     */
    void readExtraField(DataInputStream* dIn) {
      extraField = readString(extraFieldLength, dIn);
    }

    /** Liesst den Filekommentar aus den Daten aus.
     *
     * @param dIn Daten.
     */
    void readFileComment(DataInputStream* dIn) {
      fileComment = readString(fileCommentLength, dIn);
    }

};

#endif // _ZipFileHeader_h_
