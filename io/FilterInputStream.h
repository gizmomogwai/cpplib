#ifndef _FilterInputStream_h_
#define _FilterInputStream_h_

#include <io/IoApi.h>

#include <io/InputStream.h>

/** Gefilterter InputStream.
 *
 * Es wird ein Stream untergeschoben. Die Defaultimplementierungen
 * der Methoden liefert die Werte des unterliegenden Stroms, man
 * kann diese jedoch auch ueberschreiben.
 *
 * Der gewrappte stream koennte nur ueber getter und setter 
 * zugaenlich sein, das wuerde aber keinen wesentlichen vorteil bringen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2000-11-16, cK, Created.
 *  <li> 2000-11-20, cK, Commented.
 * </ul>
 *
 * @todo evtl. noch progressinputstream.
 *
 * @version $Revision: 1.3 $, $Date: 2001/09/13 13:11:10 $
 *
 * @author cK, $Author: koestlin $
 */
class IO_API FilterInputStream : public InputStream {

 public:
  /** Erzeugt einen neuen FilterInputStream auf einem zugrundeliegenden
   * InputStream. 
   *
   * @param _in InputStream.
   * @param _handleStream wird hier true angegeben wird die Verwaltung des
   *    zugrundeliegende Streams uebernommen.
   */
  FilterInputStream(InputStream* _in, bool _handleStream);
  
  /** Raeumt auf. */
  virtual ~FilterInputStream();
  
  int read() throw (IOException);
  
  int read(DataBuffer& b, int offset, int length) throw (IOException);
  int read(DataBuffer& b) throw (IOException);

 protected:
  /** Unterliegender Strom. */
  InputStream* in;
  
  /** Soll der Strom von FilterInputStream verwaltet werden. */
  bool handleStream;
  
};

#endif // _FilterInputStream_h_

