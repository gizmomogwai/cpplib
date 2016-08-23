#ifndef _PipedOutputStream_h_
#define _PipedOutputStream_h_

#include <lang/DataBuffer.h>
                         
#include <io/OutputStream.h>                         
#include <io/IOException.h>

#include <io/pipe/Pipe.h>

/** Klasse die einen Strom zur Pipe praesentiert.
 *
 * Ist genug Platz im Puffer der Pipe, wird sofort 
 * hineingeschrieben, ansonstent blockiert der Auftrag.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <lI> 2001-02-11, cK, Creted.
 * </ul>
 *
 * @todo sollte auch ne exception geworfen werden, 
 *       wenn inputstream zerstoehrt wurde???
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:31 $
 *
 * @author cK, $Author: koestlin $
 */
class PipedOutputStream : public OutputStream {
  
  public:  
    /** Erzeugt einen neuen PipedOutputStream.
     *
     * @param _ipe zugehoerige Pipe.
     */
    PipedOutputStream(Pipe* _pipe);
    
    /** Raeutm auf. */
    virtual ~PipedOutputStream();

	void write(int b) throw (IOException);

    void write(DataBuffer* b, int offset, int length) throw(IOException);


  private:
    /** Zugehoerige Pipe. */
    Pipe* pipe;
};

#endif // _PipedOutputStream_h_
