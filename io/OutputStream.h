#pragma once

#include <io/IOException.h>
#include <lang/DataBuffer.h>

/** Minimale Outputstreamschnittstelle.
 *
 * <p>
 * CurriculumVitae:
 * <ul>
 *  <li> 2000-05-14, cK, Created.
 *  <li> 2000-11-30, cK, Virtueller Deconstructor eingefuegt, 
 *       wegen nicht geschlossenen FileOutputStreams.
 *  <li> 2001-02-07, cK, flush implementiert.
 * </ul>
 *
 * @todo Exceptionhandling ueberdenken!
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:31 $
 *
 * @author cK, $Author: koestlin $
 */
class OutputStream {

	public:
    /** Raeumt auf. */
    virtual ~OutputStream() {}

		/** Schreibt ein Byte in den Strom.
		 *
		 * @param b Byte.
		 *
		 * @exception Exception wenn was nicht klappt.
		 */
		virtual void write(int b) throw (IOException) = 0;

    /** Schreibt den ganzen Datenpuffer. 
     *
     * @param b Puffer.
     */
    virtual void write(DataBuffer* b) throw (IOException) {
      write(b, 0, b->getSize());
    }
    
    /** Schreibt einen Teil des Datenpuffers.
     *
     * @param b Datenbuffer.
     * @param offset Offset des ersten zu schreibenden bytes im puffer.
     * @param length Anzahl zu schreibender bytes.
		 *
		 * @exception Exception wenn was nicht klappt.
     */
    virtual void write(DataBuffer* b, int offset, int length) throw(IOException) {
      unsigned char* data = (unsigned char*)b->getData(offset);
      for (int i=0; i<length; i++) {
        write(*data++);
      }
    }


    /** Leere flush-implementierung.
     *
     * Schreibt alle evtl. gepufferten Daten.
     */
    virtual void flush() throw (IOException) {
    }

};
