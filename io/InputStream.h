#ifndef _InputStream_h_
#define _InputStream_h_

#include <io/IoApi.h>

class DataBuffer;
#include <io/IOException.h>

/** Schnittstelle fuer minimalen Inputstream.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2000-05-14, cK, Created.
 *  <li> 2000-11-30, cK, Virtuellen Deconstructor eingefuegt 
 *       (wegen nicht geschlossenen files bei FileOutputStream).
 *  <li> 2001-04-13, cK, Um readFully erweitert.
 * </ul>
 *
 * @version $Revision: 1.3 $, $Date: 2001/09/13 13:11:10 $
 *
 * @author cK, $Author: koestlin $
 */
class IO_API InputStream {
  
 public:
  /** Virtueller Dekonstruktor. */
  virtual ~InputStream() {}
  
  /** Liest das naechste byte.
   *
   * @return int -1 falls stromende, byte anderenfalls.
	 *
	 * @exception IOException
   */
  virtual int read() throw (IOException) = 0;
  
  
  /** Versucht den DataBuffer mit bytes zu fuellen.
   *
   * @param b Buffer.
   *
   * @return int Anzahl von in den Buffer geschriebenen bytes,
   *             -1 falls strom zu ende.
	 *
	 * @exception IOException
   */
  virtual int read(DataBuffer& b) throw (IOException);

  /** Versucht einen Buffer komplett einzulesen.
   * 
   * @param b Buffer.
   *
   * @return int Anzahl tatsächlich eingelesener Byte. 
   *         Wird nichts eingelesen wird 0 zurückgeliefert.
   *
   * @exception IOException wenn etwas schief laeuft.
   */
  virtual int readFully(DataBuffer& b) throw (IOException);
  
  
  /** Versucht den DataBuffer mit bytes zu fuellen.
   * Es werden maximal length bytes eingefuellt.
   *
   * @param b Buffer.
   * @param offset Offset, ab der in den Buffer geschrieben werden soll.
   * @param length Maximale Anzahl von gelesenen Bytes.
   *
   * @return int Anzahl von gelesenen Bytes.
	 *
	 * @exception IOException wenn was nicht klappt.
   */
  virtual int read(DataBuffer& b, int offset, int length) 
		throw (IOException) = 0;

};

#endif // _InputStream_h_
