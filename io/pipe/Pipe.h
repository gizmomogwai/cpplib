#ifndef _Pipe_h_
#define _Pipe_h_

#include <io/IoApi.h>

#include <io/InputStream.h>
#include <io/OutputStream.h>

#include <lang/SyncMutex.h>

class PipedInputStream;
class PipedOutputStream;

/** Repraesentiert eine Pipe.
 *
 * Von einer Pipe kann ein InputStream und ein 
 * OutputStream angefordert werden.
 * Alles was in den OutputStream geschrieben wird ist dann 
 * am InputStream erhaeltlich.
 * Die Pipe ist mit einem Puffer ausgestattet, der es 
 * ermoeglicht writes nicht blockierend auszufuehren.
 *
 * <p>
 * Einschraenkungen:
 * <ul>
 *   <li> optimalerweise sollte die pipe von 2 threads verwendet werden
 *        der eine schreibt der andere liest.
 *   <li> werden mehr als 2 threads verwendet, kann es passieren, 
 *        dass einer von mehrerern lesenden threads nicht mehr aufwacht.
 *   <li> wird der input und outputstream von dem gleichen thread verwendet
 *        muss der puffer so gewaehlt werden, dass nie eine 
 *        blockierungssituation auftreten kann. (beim lesen muessen 
 *        immer genug daten anliegen, beim schreiben muss immer 
 *        genug platz sein)
 * </ul>
 * 
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-02-11, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:31 $
 *
 * @author cK, $Auhtor$
 */
class IO_API Pipe {

  friend class PipedInputStream;
  friend class PipedOutputStream;

  public:
    /** Erzeugt eine neue Pipe mit vorgegebener Buffergroesse. */
    Pipe(int bufferSize);

    /** Raeumt auf. */
    virtual ~Pipe();

    /** Liefert den InputStream von der Pipe.
     *
     * @return InputStream* InputStream vonder Pipe.
     */
    InputStream* getInputStream();

    /** Liefert den OutputStream zur Pipe.
     *
     * @return OutputStream* OutputStream zu der Pipe
     */
    OutputStream* getOutputStream();

  private:
    /** Strom mit dem aus der Pipe gelesen werden kann. */
    PipedInputStream* in;

    /** Strom mit dem in die Pipe geschrieben werden kann. */
    PipedOutputStream* out;

    /** Groesse des Buffers. */
    int bufferSize;

    /** Buffer. */
    unsigned char* buffer;

    /** Lock auf den Buffer. */
    SyncMutex bufferLock;

    /** Index des Bytes, das als naechstes geliefert wird. 
     * Steht nextToRead auf nextToWrite bedeutet das, dass 
     * keine Daten mehr vorliegen.
     */
    int nextToRead;

    /** Index in die das naechste Byte geschrieben werden soll. */
    int nextToWrite;

    /** Gibt an, ob der Puffer komplett leer ist. */
    bool empty;

    /** Liesst ein byte aus dem Puffer. 
     *
     * Sollte blockieren bis auch wirklic ein byte da ist.
     *
     * @param byteVal VORSICHT hier wird das byte reingeschrieben, 
     *        wenn ein byte vorhanden ist.
     *
     * @return bool true falls ein byte gelesen werden konnte
     */
    int read(unsigned char* byteVal) throw (IOException);

    /** Schreibt ein Byte in den Buffer.
     *
     * Methode blockiert bis der Wert wirklich geschrieben wurde.
     *
     * @param value wert der geschrieben werden soll.
     */
    void write(unsigned char value) throw (IOException);

    /** Raeumt mit dem OutputStream auf. */
    void deleteOutputStream();

    /** Schreibt ein byte und signalisiert einem leser, 
     * dass ein byte anliegt.
     */
    void writeByteAndSignalReader(unsigned char value);

};

#endif // _Pipe_h_
