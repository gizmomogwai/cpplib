#ifndef _URLInputStream_h_
#define _URLInputStream_h_

#include <windowsinclude.h>

#include <io/InputStream.h>
#include <io/IOException.h>

class URL;

#ifdef WIN32
#include <wininet.h>
#endif

/** URLInputStream fuer win32 urls.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-0?-??, cK, Created.
 *   <li> 2001-06-02, cK, COmmented.
 * </ul>
 *
 * @version $Revision: 1.2 $ $Date: 2001/06/05 10:02:41 $
 *
 * @author cK, $Author: koestlin $
 */
class URLInputStream : public InputStream {

 public:
  /** Erzeugt den neuen InputStream. 
   *
   * @param url URL.
   */
  URLInputStream(URL* url);
		
  /** Raeumt auf. */
  virtual ~URLInputStream();

  int read() throw (IOException);

  int read(DataBuffer* buffer, int offset, int length) throw (IOException);
		
 private:			

#ifdef WIN32
  /** Internethandle. */
  HINTERNET internet;

  /** Internetconnection. */
  HINTERNET connection;
#endif

};


#endif // _URLInputStream_h_
