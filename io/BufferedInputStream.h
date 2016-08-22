#ifndef _BufferedInputStream_h_
#define _BufferedInputStream_h_

#include <io/IoApi.h>

#include <io/FilterInputStream.h>
#include <io/IOException.h>

/** Klasse um Leseoperationen zu puffern.
 *
 * Einzelne Byte-Leseoperationen werden durch einen internen Puffer etwas
 * abgefangen. 
 *
 * In dem mini-test-programm, das nur auf fileinputstreams arbeitet 
 * konnte festgestellt werden, dass schon ein minimaler Puffer (z.b. 512
 * byte) eine geschwindigkeitssteigerung bringt. In Java ist der
 * BufferedInputStream jedoch relativ effizienter, weil in java vor allem
 * die native-aufrufe sehr teuer sind.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-29, cK, Created.
 * </ul>
 *
 * @todo Evtl. inlinen.
 *
 * @version $Revision: 1.2 $, $Date: 2001/09/13 13:11:10 $
 *
 * @author cK, $Author: koestlin $
 */
class IO_API BufferedInputStream : public FilterInputStream {

 public:
  /** Erzeugt einen neuen BufferedInputStream auf einem Stream.
   *
   * @param _in InputStream, von dem gelesen werden soll.
   * @param _handleStream soll der unterliegende Strom vom
   *        BufferedInputStream behandelt werden.
   * @param _bufferSize Groesse des zu verwendenden Puffers in Byte.
   */
  BufferedInputStream(InputStream* _in, bool _handleStream, 
                      int	_bufferSize=512);
  
  /** Raeumt auf. */
  virtual ~BufferedInputStream();
  
  int read() throw (IOException);
  
  int read(DataBuffer& buffer, int offset, int length) throw (IOException);
  
 private:
  /** Der Datenpuffer. */
  DataBuffer* buffer;
  
  /** Anzahl von gelesenen byte, bzw. anzahl von Byte, die ohne
   * leseoperation auf dem unterliegenden strom geliefert werden
   * koennen. 
   */
  int red;
  
  /** Direkter Zeiger auf das naechste Zeichen das aus dem Puffer
   * geliefert werden soll.  
   */
  unsigned char* sourceData;
  
};

#endif // _BufferedInputStream_h_
