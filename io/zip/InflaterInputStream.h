#ifndef InflaterInputStream_h_
#define InflaterInputStream_h_

#include <io/IoApi.h>

#include <io/FilterInputStream.h>
#include <lang/DataBuffer.h>
#include <io/zip/Inflater.h>

/** Entpackender FilterInputStream.
 *
 * Momentan wird das nur vom GZIPInputStream benoetigt, 
 * evtl. koennen aber noch andere streams damit arbeiten.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-15, cK, Created.
 *   <li> 2000-11-20, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/07/16 09:58:52 $
 *
 * @author cK, $Author: koestlin $
 */
class IO_API InflaterInputStream : public FilterInputStream {

 public:
  /** Erzeugt einen neuen InflaterInputStream.
   * 
   * @param _in Zugrundeliegender Strom.
   * @param _handleStream soll der Strom behandelt werden.
   * @param _inf Zu verwendender Inflator. Der Inflator wird zerstoehrt!
   * @param _bufSize Puffergroesse des dekompressionsbuffers.
   */
  InflaterInputStream(InputStream* _in, bool _handleStream,
		      Inflater* _inf, int _bufSize);
  
  /** Raeumt auf. */
  virtual ~InflaterInputStream();
  
  virtual int read() throw (IOException);
  
  virtual int read(DataBuffer& _target, int _targetOffset, int _targetLength) throw (IOException);
  
 protected:
  /** Verwendeter Infalter. */
  Inflater* inf;
  
  /** Sourcebuffer mit comprimierten Daten vom zugrundeliegenden Strom. */
  DataBuffer* sourceBuffer;
  
  /** Fuellungszustand (anzahl von bytes) im sourceBuffer. */
  int fillState;

  /** Fuellt den SourceBuffer. */
  virtual void fill();
   
  /** Ende des Stroms erreicht. */
  bool eofReached;

};

#endif // _InflaterInputStream_h_
