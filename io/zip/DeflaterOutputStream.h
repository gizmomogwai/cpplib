#ifndef _DeflaterOutputStream_h_
#define _DeflaterOutputStream_h_

#include <io/FilterOutputStream.h>
#include <io/OutputStream.h>
#include <io/IOException.h>
#include <lang/ByteDataBuffer.h>
#include <io/zip/Deflater.h>

/** Implementiert einen Outputstream mithilfe von Deflate (zlib).
 *
 * Basis fuer z.b. GZIPOutputStream.
 * 
 * Basiert auf der java-implmentierung.
 *
 * Schreibt bei write Daten in den Deflater (setInput) und ruft so lange 
 * deflate auf, bis neuer Input vom Deflater gefordert wird.
 *
 * <p>
 * Curriculum Vitae.
 * <ul>
 *   <li> 2001-04-08, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/06/05 10:02:40 $
 *
 * @author cK, $Author: koestlin $
 */
class DeflaterOutputStream : public FilterOutputStream {

  public:
    /** Erzeugt einen neuen DeflaterOutputStream.
     *
     * @param out Unterliegender Strom.
     * @param handleStream soll stream geschlossen werden.
     * @param def Deflater geht in den Besitz des DeflaterOutputStreams ueber.
     * @param size Buffergroesse.
     */
    DeflaterOutputStream(OutputStream* out, bool handleStream, Deflater* _def, int size=512) 
      : FilterOutputStream(out, handleStream), def(_def) {

      if (def == 0) {
        throw(Exception("DeflaterOutputStream() - deflater == 0", 
                        __FILE__, __LINE__));
      } else if (size <= 0) {
        throw(Exception("DeflaterOutputStream() :: buffersize <= 0", 
                        __FILE__, __LINE__));
      }
      buf = new ByteDataBuffer(size);
    }

    /** Raeumt auf. */
    virtual ~DeflaterOutputStream() {
      if (def != 0) {
        finishCompression();
        delete(def);
        def = 0;
      }
      if (buf != 0) {
        delete(buf);
        buf = 0;
      }
    }

    void write(int b) throw (IOException) {
      unsigned char data[1];
      data[0] = b & 0xff;
      DataBuffer buffer(data, 1, false);
      write(&buffer, 0, 1);
    }

    void write(DataBuffer* b, int off, int len) throw (IOException) {
      if (def->isFinished()) {
        throw(IOException("DeflaterOutputStream - write beyond end of stream", 
                          __FILE__, __LINE__));
	    }
      if ((off < 0) || (len < 0) || ((off + len) < 0) | (((b->getSize() - (off + len)) < 0))) {
        throw(Exception("DeflaterOutputStream - index out of bounds", 
                        __FILE__, __LINE__));
      } else if (len == 0) {
	      return;
	    }
	    if (def->isFinished() == false) {
        def->setInput(b, off, len);
        while (def->needsInput() == false) {
		      deflate();
        }
	    }
    }


  protected: 
    /** Packer. */
    Deflater* def;

    /** Datenpuffer. */
    ByteDataBuffer* buf;
  
    /** Abschliessen der Kompression. */
    void finishCompression() {
      if (def->isFinished() == false) {
        def->pleaseFinish();
	      while (def->isFinished() == false) {
		      deflate();
	      }
	    }
    }

    /** Packt in den intern verwendeten Puffer. */
    void deflate() throw (IOException) {
	    int len = def->deflate(buf, 0, buf->getSize());
	    if (len > 0) {
        out->write(buf, 0, len);
	    }
    }

};

#endif // _DeflaterOutputStream_h_
