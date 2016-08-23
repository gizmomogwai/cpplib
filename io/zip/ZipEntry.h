#ifndef _ZipEntry_h_
#define _ZipEntry_h_

#include <lang/Exception.h>
#include <io/file/File.h>
#include <io/file/FileInputStream.h>
#include <io/LittleEndianDataInputStream.h>
#include <io/zip/ZipFileHeader.h>
#include <io/RestrictedInputStream.h>

#include <io/zip/ZipEncryptedInputStream.h>
#include <io/zip/ZipInflaterInputStream.h>

/** Ein ZipEintrag mit header und den eignetlichen nutzdaten.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   2001-07-13, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2001/07/16 09:58:52 $
 *
 * @author cK $Author: koestlin $
 */
class ZipEntry {
	
  public:
    /** Erzeugt aus einer headerbeschreibung und einem File den
     * Zipeintrag und liesst den localheader aus.
     *
     * @param header Beschreibung der Position des ZipEintrags.
     * @param f File in dem der eintrag ist.
     */
	  ZipEntry(ZipFileHeader* header, File* f) 
		  : fileName(0), extraField(0), dataOwned(true) {

		  FileInputStream* fIn = 
			  new FileInputStream(f, header->offsetOfLocalHeader);
		  LittleEndianDataInputStream dIn(fIn, false);
		  unsigned int signature = dIn.readInt();
		  if (signature != 0x04034b50) {
			  throw(Exception("illegal signature", __FILE__, __LINE__));
		  }
		  needed2Extract = dIn.readShort();
		  generalPurpose = dIn.readShort();
		  if ((generalPurpose & 0x0004) != 0) {
			  throw(Exception("length is given in the data descriptor", 
											  __FILE__, __LINE__));
		  }
		  compressionMethod = dIn.readShort();
		  lastModTime = dIn.readShort();
		  lastModDate = dIn.readShort();
		  crc32 = dIn.readInt();
		  compressedSize = dIn.readInt();
		  uncompressedSize = dIn.readInt();
		  fileNameLength = dIn.readShort();
		  extraFieldLength = dIn.readShort();
		  readFileName(&dIn);
		  readExtraField(&dIn);
      data = new RestrictedInputStream(fIn, compressedSize, true);
	  }

    /** Raeumt auf. */
	  virtual ~ZipEntry() {
		  if (dataOwned == true) {
			  delete(data);
		  }
      if (fileName != 0) {
        delete(fileName);
      }
      if (extraField != 0) {
        delete(extraField);
      }
	  }

    /** Liefert die Daten. 
     *
     * @param passwd Password (kann auch 0 sein). Bleibt im 
     *        Besitz des Callers.
     *
     * @return InputStream* Die Daten.
     */
    InputStream* getData(std::string* passwd) {

      InputStream* res = 0;
    
      if (isEncrypted() == true) {
        res = new ZipEncryptedInputStream(data, true, passwd, crc32);
      } else {
        res = data;
      }

      InputStream* res2 = 0;
      if (compressionMethod == 0) {
        res2 = res;
      } else if (compressionMethod == 8) {
        // deflate is used
        res2 = new ZipInflaterInputStream(res, true, 1024);
      }

		  dataOwned = false;
      return(res2);
	  }

    /** Testet anhand des GeneralPurposeflags, ob die Daten encrypted sind.
     *
     * @return bool true falls die daten verschluesselt sind.
     */
    bool isEncrypted() {
      return((generalPurpose & 0x0001) != 0);
    }

    /// siehe FileHeader.
    unsigned short needed2Extract;

    /// siehe FileHeader.
    unsigned short generalPurpose;

    /// siehe FileHeader.
    unsigned short compressionMethod;

    /// siehe FileHeader.
    unsigned short lastModTime;

    /// siehe FileHeader.
    unsigned short lastModDate;
	  
    /// siehe FileHeader.
    unsigned int crc32;

    /// siehe FileHeader.
    unsigned int compressedSize;
 
    /// siehe FileHeader.
    unsigned int uncompressedSize;

    /// siehe FileHeader.
    unsigned short fileNameLength;

    /// siehe FileHeader.
    unsigned short extraFieldLength;

    /// siehe FileHeader.
    std::string* fileName;
	  
    /// siehe FileHeader.
    std::string* extraField;

  private:	
    /** Wird der Strom noch vom ZipEntry verwaltet, 
     * oder hat der Entry sein Recht verloren.
     */
	  bool dataOwned;

    /** Die Daten. */
	  InputStream* data;

    /** Liesst einen String einer bestimmten Laenge vom DataInputStream.
     *
     * @param length Laenge des String.
     * @param dIn DataInputStream.
     *
     * @return std::string* string oder 0.
     */
    std::string* readString(int length, DataInputStream* dIn) {
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

    /** Liesst den Filenamen des Eintrags.
     *
     * @param dIn DataInputStream
     */
    void readFileName(DataInputStream* dIn) {
      fileName = readString(fileNameLength, dIn);
    }

    /** Liesst das Extrafield des Eintrags.
     *
     * @param dIn DataInputStream.
     */
    void readExtraField(DataInputStream* dIn) {
      extraField = readString(extraFieldLength, dIn);
    }

};

#endif // _ZipEntry_h_
