#pragma once

#include <io/OutputStream.h>
#include <lang/ByteDataBuffer.h>

/** OutputStream, der auf einem sich vergroessernden Speicher arbeitet.
 *
 * <p>
 * Curriclum Vitae:
 * <ul>
 *   <lI> 2001-01-09, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:31 $
 *
 * @author cK, $Author: koestlin $
 */
class ByteArrayOutputStream : public OutputStream {

 public:
  /** Erzeugt einen neuen OutputStream mit initialer groesse.
   *
   * @param _initialSize.
   */
  ByteArrayOutputStream(long _initialSize, bool clear=false);
  
  /** Raeumt auf. */
  virtual ~ByteArrayOutputStream();
  
  void write(int b) throw (IOException);
  
  void write(DataBuffer* b, int offset, int length) throw (IOException);
  
  
  /** Liefert die Anzahl wirklich gechriebener Bytes.
   *
   * @return int Anzahl von geschriebenen Byte.
   */
  unsigned int getBytesWritten();
  
  /** Liefert den Datenpuffer. 
   *
   * @return ByteDataBuffer* Daten. Der Puffer wird vom Stream 
   *         zerstoehrt, darf also nicht von der Applikation 
   *         freigegeben werden.
   */
  ByteDataBuffer& getData();
  
  
 private:
  /** Speicher, in den geschrieben wird. */
  ByteDataBuffer* output;
  
  /** Anzahl von geschriebenen Bytes. */
  unsigned int written;
  
  /** Sichert, dass im output genug platz ist. 
   *
   * @param size Groesse, an byte, die noch in den Buffer passen muessen.
   */
  void assertSpace(unsigned int size);
  
};
