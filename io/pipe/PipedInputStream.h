#ifndef _PipedInputStream_h_
#define _PipedInputStream_h_

#include <io/IoApi.h>

#include <lang/DataBuffer.h>
#include <io/InputStream.h>
#include <io/IOException.h>
#include <io/pipe/Pipe.h>

/** Klasse die einen InputStream von einer Pipe realisiert.
 *
 * Der Strom wird verwendet um von einer Pipe zu lesen.
 * Wird auf einer Pipe gelesen, die keine Daten mehr hat, 
 * blockiert der Leseauftrag, bis wieder Daten anliegen.
 * Wird auf einer Pipe gelesen, deren OutputStrem schon 
 * zerstoehrt wurde werden noch alle Daten im Puffer 
 * ausgelesen, danach wird beiden read operationen -1 geliefert.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <lI> 2001-02-11, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:31 $
 *
 * @author cK, $Author: koestlin $
 */
class IO_API PipedInputStream : public InputStream {  

  public:
    /** Erzeugt einen PipedInputStream.
     *
     * @param pipe ZTugehoerige Pipe.
     */
    PipedInputStream(Pipe* pipe);

    /** Raeumt auf. */
    virtual ~PipedInputStream();

    int read() throw (IOException);
  
    int read(DataBuffer& b, int offset, int length) throw (IOException);

  private:
    /** Zugehoerige Pipe. */
    Pipe* pipe;

};
                              
#endif // _PipedInputStream_h_
