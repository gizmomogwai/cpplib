#ifndef _SocketInputStream_h_
#define _SocketInputStrean_h_

#include <net/Socket.h>
#include <io/InputStream.h>
#include <lang/DataBuffer.h>

/** InputStream, der auf einem Socket arbeitet.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-05-14, cK, Created.
 *   <li> 2001-03-31, cK, besser an throw klauseln von InputStream gehalten
 * </ul>
 *
 * @todo Gibts ne moeglichkeit das auslesen der Daten im deconstructor zu
 *       vermeiden, oder ist das sowieso schon lokal auf dem rechner,
 *       belastet das netz also nicht mehr??? ich glaube man muss das
 *       sowieso weglassen!
 * @todo muessen die daten wirklich ausgelesen werden ... in der
 *       winsockapidocu steht eigentlich: if there is still data queued on
 *       the socket waiting to be received, or data arrives subsequently,
 *       the connection is reset,  
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:32 $
 *
 * @author cK, $Author: koestlin $
 */
class SocketInputStream : public InputStream {
  
 public:
  /** Erzeugt einen neuen SocketInputStream auf einem Socket.
   *
   * @param s Socket.
   */
  SocketInputStream(Socket* s);
  
  /** Zerstoehrt/schliesst den InputStream.
   *
   * Setzt den InputStream auch im Socketobjekt auf 0.
   * Liesst alle Daten aus, die noch auf dem Socket sind.
   */
  virtual ~SocketInputStream();
  
  int read() throw (IOException);
  
  int read(DataBuffer& b, int offset, int length) throw (IOException);
  
 private:
  /** Zugrundeliegender Socket. */
  Socket* s;
  
};

#endif // _SocketInputStream_h_
