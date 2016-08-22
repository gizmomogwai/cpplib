#ifndef _ByteDataBuffer_h_
#define _ByteDataBuffer_h_

#include <lang/DataBuffer.h>

/** Datenbuffer fuer unsinged chars.
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:35 $
 *
 * @author cK, $Author: gizmo $
 */
class LANG_API ByteDataBuffer : public DataBuffer {

 public:

  /** Selbstverwalteter Byte-Buffer. 
   *
   * @param size Anzahl von Bytes im Buffer.
   **/
  ByteDataBuffer(int size);
  ByteDataBuffer(const unsigned char* data, size_t length);

  /** Erzeugt einen leeren Bytebuffer. 
   *
   * setData ist zwingend erforderlich. 
   **/
  ByteDataBuffer();
		
  /** Raeumt auf. **/	
  virtual ~ByteDataBuffer();
		
};

#endif
