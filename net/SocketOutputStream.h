#pragma once

#include <net/Socket.h>
#include <io/OutputStream.h>
#include <lang/DataBuffer.h>

/** OutputStream, der auf einem Socket agiert.
 *
 * Der strom kann unabhaengig vom InputStream geschlossen werden.
 * Wird der strom einmal geschlossen, kann jedoch kein neuer mehr auf dem
 * socket aufgebaut werden.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-05-14, cK, Created.
 * </ul>
 *
 * @todo Ganz gut ist das noch cniht gemahct, da
 *       bei send nicht nur alles oder nichts gesendet wird ...
 *       evtl. koennte es also, wenn man mitten in einer
 *       uebertragung getrennt wird zu problemen kommen ..
 *       aber dann muss halt der empfaenger irgendwie sagen
 *       wo er weitermachen will
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:32 $
 *
 * @author cK, $Author: koestlin $
 */
class SocketOutputStream : public OutputStream {

 public:
  /** Erzeugt den Socket Outputstream auf einem Socket.
   *
   * @param s Socket.
   */
  SocketOutputStream(Socket* s);

  /** Zerstoehrt den OutputStream.
   *
   * Setzt den OutputStream des Sockets auch auf 0.
   */
  virtual ~SocketOutputStream();

  virtual void write(int b) throw (IOException);

  virtual void write(DataBuffer* b, int offset, int length)
    throw (IOException);

 private:
  /** Zugrundeliegender Socket. */
  Socket* socket;
};
