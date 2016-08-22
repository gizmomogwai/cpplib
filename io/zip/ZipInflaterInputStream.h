#ifndef _ZipInflaterInputStream_h_
#define _ZipInflaterInputStream_h_

#include <io/IoApi.h>

#include <io/zip/InflaterInputStream.h>

/** Inflater InputStream fuer ZipEntrys.
 *
 * Es muss ein fake 0 byte ans ende angehaengt werden :((
 * Hab ich von java abgeschaut.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-07-13, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2001/07/16 09:58:52 $
 *
 * @author ck $Auhor$
 */
class IO_API ZipInflaterInputStream : public InflaterInputStream {

  public:
    /** InflaterInputStream ohne HZIPheader etc.
		 *
		 * @param _in InputStream
		 * @param _handleStream Soll Stream uebernommen werden.
		 * @param _bufSize Buffergroesse.
		 */
    ZipInflaterInputStream(InputStream* _in, 
		  										 bool _handleStream, 
			  									 int _bufSize) 
      : InflaterInputStream(_in,
	  												_handleStream, 
		  											new Inflater(true), 
			  										_bufSize) {
    }
   
	  /** 0-byte-fake.
		 */
    void fill() {
      if (eofReached == true) {
	  		throw(Exception("Unexpected end of ZLIB input stream", 
		  									__FILE__, __LINE__));
      }
      
      fillState = in->read(*sourceBuffer, 0, sourceBuffer->getSize());
      if (fillState == -1) {
        fillState = 1;
        char* help = (char*)sourceBuffer->getData();
        help[0] = 0;
        eofReached = true;
      }
      inf->setInput(sourceBuffer, 0, fillState);  
    }

};

#endif // _ZipInflaterInputStream_h_
