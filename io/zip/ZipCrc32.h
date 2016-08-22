#ifndef _ZipCrc32_h_
#define _ZipCrc32_h_

#include <io/IoApi.h>

#include <io/zip/Checksum.h>

/** Spezieller Crc um die encryptionkeys zu updaten.
 *
 * Keine Ahnung, warum das nicht ein normaler CRC32 tut.
 *
 * Aus dem unzip-source uebernommen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-07-13, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2001/07/16 09:58:52 $
 *
 * @author cK $Author: koestlin $
 */
class IO_API ZipCrc32 : public Checksum {

  public:
  	/** Tabelle. */
  	const static unsigned long crc32Tab[];

  	/** Erzeugt das Checksummenobjekt. */
    ZipCrc32() {
    }

  	/** Uebernimmt einen Wert. */
    void update(int b) {
      crc = (crc32Tab[(crc ^ b) & 0xff]) ^ (crc >> 8);
    }

};

#endif // _ZipCrc32_h_
