#ifndef _GZIPOutputStream_h_
#define _GZIPOutputStream_h_

#include <io/IoApi.h>


#include <io/OutputStream.h>
#include <io/IOException.h>
#include <io/zip/DeflaterOutputStream.h>
#include <io/zip/CRC32.h>


/** Klasse die GZIPOutput erzeugt.
 *
 * Von den java-sourcen adapterit.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-08, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:31 $
 *
 * @author cK, $Author: koestlin $
 */
class IO_API GZIPOutputStream : public DeflaterOutputStream {

  public: 
    /** Erzeugt einen GZIPOutputStream.
     *
     * @param out Unterliegender Strom.
     * @param handleStream soll stream geschlossen werden.
     * @param level Compressionslevel (0-9)
     * @param size Buffergroesse.
     */
    GZIPOutputStream(OutputStream* out, 
                     bool handleStream, 
                     int level=Deflater::DEFAULT_COMPRESSION, 
                     int size=512) throw (IOException) 
      : DeflaterOutputStream(out, handleStream, new Deflater(level, true), size) {

      crc = new CRC32();
      writeHeader();
      crc->reset();

    }

    /** Raeumt auf. */
    virtual ~GZIPOutputStream() {
      finishGZIP();
      delete(crc);
    }

    void write(DataBuffer* buf, int off, int len) throw (IOException) {
      DeflaterOutputStream::write(buf, off, len);
	    crc->update(buf, off, len);
    }

  protected: 
    /** CRC32 ueber die originaldaten. */
    CRC32* crc;;
    
    /** Komprimiert fertig und schreibt den GZIPTrailer. */
    void finishGZIP() {

      if (def->isFinished() == false) {
        def->pleaseFinish();
        while (def->isFinished() == false) {
          deflate();
        }
        writeTrailer();
	    }
    }

  private: 
    /** GZIPMagicheader. */
    const static int GZIP_MAGIC;

    /** Schreibt den GZIPHeader. 
     * Magic, compressionmethod, flags, modtime, extraflags, os.
     */
    void writeHeader() throw (IOException) {
	    writeShort(GZIP_MAGIC);	    // Magic number
      out->write(def->DEFLATED);    // Compression method (CM)
	    out->write(0);		    // Flags (FLG)
	    writeInt(0);		    // Modification time (MTIME)
	    out->write(0);		    // Extra flags (XFL)
	    out->write(0);		    // Operating system (OS)
    }
    
    /** Schreibt den Trailer.
     * CRC32 und originalDatenlaenge.
     */
    void writeTrailer() throw (IOException) {
	    writeInt((int)crc->getChecksum());  // CRC-32 of uncompressed data
	    writeInt(def->getTotalIn());	// Number of uncompressed bytes
    }
    
    /** Schreibt 32bit in PC-Endian. 
     *
     * @param i int (32bit).
     */
    void writeInt(int i) throw (IOException) {
	    writeShort(i & 0xffff);
	    writeShort((i >> 16) & 0xffff);
    }
    
    /** schreibt 16bit in PC-Endian.
     *
     * @param s short (16 bit).
     */
    void writeShort(int s) throw (IOException) {
	    out->write(s & 0xff);
	    out->write((s >> 8) & 0xff);
    }

};

#endif // _GZIPOutputStream_h_
