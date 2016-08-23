#ifndef _Checksum_h_
#define _Checksum_h_

#include <lang/DataBuffer.h>

/** Schnittstelle fuer Checksummenalgorithmen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2000-11-20, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/07/16 09:58:52 $
 *
 * @author cK, $Auzthor$
 */
class Checksum {
	
	public:

	virtual ~Checksum() {
	}
	
    /** Setzt die Checksumme auf einen Wert. 
     *
     * @param value Neuer Wert der Checksumme.
     */
    void setChecksum(unsigned long value) {
      crc = value;
    }
		
		/** Liefert die Checksumme zurueck. 
		 *
		 * @return int Checksumme.
		 */
		virtual unsigned long getChecksum() { 
			return(crc); 
		}
		
		/** Resetiert die Checksummenberechnung, so dass das gleiche Objekt zu
		 * einer neuen Checksummenberechnung verwendet werden kann.
		 */
		virtual void reset() { 
			crc = 0; 
		}
		
		/** Updated die Checksumme mit einem Byte.
		 *
		 * @param b Byte.
		 */
		virtual void update(int b) = 0;
		
		/** Updated die Checksumme mit den Daten die in b stehen.
		 *
     * @param b Buffer mit neuen Daten.
		 * @param offset Offset in die Daten, ab der die Checksumme berechnet
		 *        werden soll.
		 * @param length Anzahl von Bytes die zur berechnung hinzugezogen 
		 *        werden sollen.
		 */
    virtual void update(DataBuffer* b, int offset, int length) {
      char* data = (char*)b->getData(offset);
      for (int i=0; i<length; i++) {
        update(*data++);
      }
    }
		
	protected:
    /** Bisher berechnete Checksumme. */
		unsigned long crc;
	
};

#endif // _Checksum_h_
