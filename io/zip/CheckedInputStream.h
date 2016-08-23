#ifndef _CheckedInputStream_h_
#define _CheckedInputStream_h_

#include <io/FilterInputStream.h>
#include <io/zip/Checksum.h>

/** FilterInputStream, der beim lesen des Stroms eine Checksumme
 * berechnet. 
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2000-11-20, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/07/16 09:58:52 $
 *
 * @author cK, $Author: koestlin $
 */
class CheckedInputStream : public FilterInputStream {
  
 public:
  /** Erzeugt einen neuen CheckedStrom.
   *
   * @param _in Zugrundeliegender Strom.
   * @param _handleStream soll der Strom verwaltet werden.
   * @param _check Checksummenalgorithmus, wird nicht befreit, bleibt also im besitz des callers.
   */
  CheckedInputStream(InputStream* _in, bool _handleStream, 
		     Checksum* _check);
  
  /** Raeumt auf. */
  virtual ~CheckedInputStream();
  
  int read() throw (IOException);
  
  int read(DataBuffer& _b, int _offset, int _length) throw (IOException);
  
  /** Liefert die Checksumme der bisher gelesenen Daten.
   *
   * @return int Checksumme.
   */
  virtual unsigned long getChecksum();
  
  
 protected:
  /** Checksummenalgorithmus. */
  Checksum* check;
  
};

#endif // _CheckedInputStream_h_
