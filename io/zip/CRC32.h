#ifndef _CRC32_h_
#define _CRC32_h_

#include <io/zip/Checksum.h>
#include <lang/DataBuffer.h>

/** Berechnet eine CRC32 Checksumme.
 *
 * Verwendet den crc-Algorithmus der ZLIB (1.1.3)
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-20, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:31 $
 *
 * @author cK, $Author: koestlin $
 */
class CRC32 : public Checksum {

 public:
	/** Erzeugt ein neues Checksummenobjekt. */
	CRC32();

	/** Raeumt auf. */
	virtual ~CRC32();
		
	/** Updated die Checksumme mit einem byte. */
	void update(int b);
		
	/** Updated die Checksumme mit einer Menge von Byte. 
	 *
	 * @param _b Datenpuffer mit neuen Daten.
	 * @param _offset Offset in den Datenpuffer.
	 * @param _length Anzahl neuer Daten.
	 */
	void update(DataBuffer* _b, int _offset, int _length);
	
};

#endif // _CRC32_h_
