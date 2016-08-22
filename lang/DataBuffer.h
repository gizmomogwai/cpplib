#ifndef _DataBuffer_h_
#define _DataBuffer_h_

#include <lang/LangApi.h>

#include <lang/Exception.h>

/** Kapselt Daten (aehnlich einem array in java).
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:35 $
 *
 * @author cK, $Author: gizmo $
 */
class LANG_API DataBuffer {

 public:
	/** Erzeugt einen neuen Datenpuffer.
	 *
	 * @param _data Datenpointer.
	 * @param _length Groesse des Puffers.
	 * @param _ownMem falls true sollten unterklassen den uebergebenen
	 *	 speicher aufraeumen. Das funktioiert nur bei unterklassen, da die
	 *	 evtl. wissen koennen, wie der speicher allokiert wurde.
	 */
        DataBuffer(void* _data, const int _length, bool _ownMem);
		
	/** raeumt auf. */
	virtual ~DataBuffer();
		
	/** setzt die daten. 
	 * 
	 * @parma _data Zeiger auf die Daten, die verwaltet werden sollen.
	 * @param _length Groesse des Puffers.
	 * @param _ownMem (soll der Speicher selbst verwaltet werden.
	 */
	void setData(void* _data, int _length, bool _ownMem);
		
	/** Liefert die Daten. 
	 *
	 * @return void Daten als void*.
	 *
	 * @exception Exception falls keine Daten gesetzt sind.
	 */
	void* getData() throw (Exception);
		
	/** Liefert die Daten ab einem offset. 
	 * 
	 * @param offset Offset ab dem die Daten geliefert werden sollen.
	 *
	 * @return void* Daten als void*.
	 *
	 * @exception Exception falls der offset ungueltig ist (<0 oder >=
	 *	 length). 
	 */
	void* getData(unsigned int offset) throw (Exception);
		
	/** Liefert die Groesse des Puffers.
	 *
	 * @return int Groesse des Puffers.
	 */
	unsigned int getSize();
		
	/** Setzt die Daten auf 0. */
	void clear();
		
 protected:
	/** Soll der Speicher selbst verwaltet werden. */
	bool ownMem;

 private:
	/** Daten. */
	void* data;

	/** Groesse des Puffers. */
	unsigned int length;

};

#endif // _DataBuffer_h_
