#ifndef GZIPInputStream_h_
#define GZIPInputStream_h_

#include <io/zip/InflaterInputStream.h>
#include <lang/DataBuffer.h>
#include <io/zip/CRC32.h>

/** Stellt einen GZIPInputStream zur verfuegung.
 *
 * Im wesentlichen muss der GZIP-Header und Trailer verarbeitet werden, der
 * Rest wird vom InflaterInputStream erledigt.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2000-11-5, cK, Created.
 *  <li> 2000-11-20, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/07/16 09:58:52 $
 *
 * @author cK, $Author: koestlin $
 */
class GZIPInputStream : public InflaterInputStream {
  
 public:
  /** Erzeugt einen neuen GZIPInputStream auf dem zugrundeliegenden
	 * InputStream. 
   *
   * @param _in InputStream
   * @param _handleStream Soll der unterliegende Streasm verwealtet werden.
   * @param _size Puffergroesse des GZIP-Algorithmusses.
   */
  GZIPInputStream(InputStream* _in, 
                  bool _handleStream, 
                  int _size=512);
  
  /** Raumt auf. */
  virtual ~GZIPInputStream();
  
  int read() throw (IOException);

  int read(DataBuffer& _target, int _offset, int _length) throw (IOException);
  
 private:
  /** Verwendete Checksumme. */
  CRC32* crc;
  
  /** Ist der Stream fertig dekomprimiert. */
  bool eos;
  
  /** Ist der Strom geschlossen. */
  bool closed;

  bool containsZlibWrapper;
  
  /** GZIP header magic number. */
  static const int GZIP_MAGIC;  
  
  /** File header flag - Extra Text. */
  static const int FTEXT;
  
  /** File header flag - Header CRC. */
  static const int FHCRC;
  
  /** File header flag - Extra Field. */
  static const int FEXTRA;
  
  /** File header flag - File Name. */
  static const int FNAME;
  
  /** File header flag - FileComment. */
  static const int FCOMMENT;
  
  /** Liesst den GZIPHeader ein. */
  void readHeader();
  
  /** Liesst den GZIP-Trailer ein. */
  void readTrailer();
  
  /** Liesst ein Short (16bit) in pc-endian. 
   *
   * @param _in InputStream, von dem die Daten gelesen werden sollen.
   */
  unsigned short readUShort(InputStream* _in);
  
  /** Liesst ein Int (32bit) in pc-endian ein.
   *
   * @param _in InputStream, von dem die Daten gelesen werden sollen.
   */
  long readUInt(InputStream* _in);
  
  /** Ueberspringt eine Menge von byte im InputStream.
   *
   * @param _in InputStream.
   * @param bytes Anzahl uzu ueberspringender Byte.
   */
  void skipBytes(InputStream* _in, int _bytes);
  
  /** Behandelt das Ende eines GZIP-Stroms. 
   *
   * @param _in InputStream.
   */
  void handleRest(InputStream* _in);
  
};


#endif // _GZIPInputStream_h_
