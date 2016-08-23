#ifndef _Base64OutputStream_h_
#define _Base64OutputStream_h_

#include <io/FilterOutputStream.h>

/** Filteroutputstream, der eine mim64 kodierung erzeugt.
 *
 * Beschreibung in rfc 1521.
 *
 * Es werden immer 3 byte zusammengefasst. diese 3 byte werden dann
 * auf ein alphabet mit 64 zeichen abgebildet. A-Z, a-Z, 0-9, +/
 *
 * Zusaetzlich werden zeilen erzeugt, die maximal 74 zeichen + 
 * 0xd 0xa gross sind. 
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-03-??, cK, Created.
 *   <li> 2001-03-31, cK, Commented und an linux angepasst (throw IOException).
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:31 $
 *
 * @author cK, $Author: koestlin $
 */
class Base64OutputStream : public FilterOutputStream {
  
 public:
  /** Erzeugt den outputstream.
   *
   * @param os Unterliegender stream.
   * @param handleStream sollte der unterliegende verwaltet werden.
   */
  Base64OutputStream(OutputStream* os, bool handleStream) 
    : FilterOutputStream(os, handleStream), current(0), bytesOutputted(0) {
  }

  /** Raeumt auf. */  
  virtual ~Base64OutputStream() {
    flush();
  }
  
  void write(int b) throw (IOException);
  
  void flush() throw (IOException);
  
 private:

  /** Puffert immer 3 byte zusammen und schreibt diese dann raus. */  
  void doWrite() throw (IOException);
  
  /** tablele mit den 64 verwendeten zeichen. */
  static const char table[64];
  
  /** puffer fuer die 3 auszugebenden byte. */
  unsigned char data[3];
  
  /** welches byte kommt als naechstes in den puffer. */
  unsigned short current;
  
  /** zaehler der die zeichen einer zeile zaehlt. */
  unsigned short bytesOutputted;
  
};


#endif
