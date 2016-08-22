#ifndef _RestrictedInputStream_h_
#define _RestrictedInputStream_h_

#include <io/IoApi.h>

#include <io/InputStream.h>
#include <io/FilterInputStream.h>
#include <lang/DataBuffer.h>
                                                       
/** FilterInputStream, der die Daten direkt von 
 * dem unterliegenden Strom liefert, allerdings nur eine
 * gewisse menge. Sind mehr daten im Stream vorhanden
 * werden nur soviele Daten geliefert, wie der strom 
 * eingeschraenkt ist. 
 * Sind zu wenig Daten vorhanden wird eine Exception geworfen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul> 
 *   <li> 2001-03-13, cK, Created.
 * </ul>                          
 *
 * @version $Revision: 1.3 $, $Date: 2001/07/16 09:59:46 $
 *
 * @author cK, $Author: koestlin $
 */                                                       
class IO_API RestrictedInputStream : public FilterInputStream {
 public:
	/** Erzeugt einen Stream mit n byte groesse.
	 *
	 * @param in Unterliegender Strom.
	 * @param _n Anzahl von bytes.
	 * @param handleStream soll der Stream am ende aufgeraeumt werden.
	 */
	RestrictedInputStream(InputStream* in, 
												long _n, 
												bool handleStream) 
    : FilterInputStream(in, handleStream), n(_n) {
	}     
    
	/** Raeumt auf. */
	virtual ~RestrictedInputStream() {
	}
      
	int read() throw (IOException) {
      
		if (n > 0) {
			int res = in->read();
			if (res == -1) {
				throw(IOException("RestrictedInputStream::read() - eof", 
													__FILE__, __LINE__));
			}
			n--;
			return(res);
		} else {
			return(-1);
		}
	}

	int read(DataBuffer& data, int offset, int length) throw (IOException) {
		if (n>0) {
			int maxRead = ((int)n < length) ? n : length;
			int red = in->read(data, offset, maxRead);
			if (red == -1) {
				throw(IOException("RestrictedInputStream::read(DataBuffer, ...) - eof", 
													__FILE__, __LINE__));
			}
			n -= red;
			return(red);
		} else {
			return(-1);
		}
	}

    
 private:
	/** Anzahl von Bytes die angeboten werden sollen. */
	unsigned long n;
    
};

#endif // _RestrictedInputStream_h_
