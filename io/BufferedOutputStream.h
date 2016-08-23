#pragma once

#include <lang/ByteDataBuffer.h>
#include <io/IOException.h>
#include <io/OutputStream.h>
#include <io/FilterOutputStream.h>


/** BufferedOutputStream.
 *
 * Der BufferedOutputStreasm soll verhindern, dass das 
 * schreiben einzelner oder weniger Byte sofort auf den 
 * richtigen Stream durchschlaegt.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-02-07, cK, Created
 *   <li> 2001-04-08, cK, Bugfix in write(DataBuffer*)     
 *        void* dst = buffer->getData(count) musste es heissen statt getData();
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:31 $
 *
 * @author cK, $Author: koestlin $
 */
class BufferedOutputStream : public FilterOutputStream {

  public:    
    /** Erzeugt einen neuen BufferedOUtputStream auf 
     * einem zugrundeliegenden OutputStream. 
     * Es kann eine Puffergroesse angegeben werden.
     * Wird nichts angegeben wird eine Puffergroesse von 512 byte verwendet.
     *
     * @param _out Unterliegender OutputStream.
     * @param _handleStream flag, ob der stream uebernommen werden soll.
     * @param _size Groesse des Puffers (default 512).
     */
    BufferedOutputStream(OutputStream* out, bool _handleStream, int _size=512);

    /** Raeumt auf. */
    virtual ~BufferedOutputStream();


    /** Schreibt ein Byte.
     *
     * Ist der Puffer voll, wird der Puffer zunaechst geleert.
     *
     * @param b Byte.
     *
     * @param IOException Exception.
     */
    void write(int b) throw (IOException);

    /** Schreibt einen Buffer.
     *
     * <ul>
     *   <li> Ist die zu schreibende Menge von Daten groesser als der 
     *        interne Buffer wird sofort geschrieben und auch die Daten 
     *        werden sofort geschrieben, fertig.
     *   <li> Passt die zu schreibende Datenmenge nicht mehr in den Buffer,
     *        wird der Buffer geschrieben.
     *   <li> Danach werden die Daten in den Puffer kopiert.
     * </ul>
     *
     * @param _buffer zu schreibende Daten.
     * @param _offset Offset in die Daten.
     * @param _length Anzahl von Byte.
     */
    void write(DataBuffer* _buffer, int _offset, int _length) throw (IOException);

    /** Flushimplementierung.
     *
     * Es wird zunaechst der Buffer rausgeschrieben, 
     * dann das normale flush aufgerufen.
     */
    void flush() throw (IOException);

  private:
    /** Flusht den Internen Buffer. */
    void flushBuffer() throw (IOException);

    /** Buffer, in den die Daten zunaechst geschrieben werden. */
    ByteDataBuffer* buffer;

    /** Anzahl schon geschriebener Byte im Buffer. */
    int count;

};
