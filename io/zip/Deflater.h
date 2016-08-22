#ifndef _Deflater_h_
#define _Deflater_h_

#include <io/IoApi.h>

#include <lang/DataBuffer.h>
#include <zlib.h>

#include <iostream>
#include <stdlib.h>

/** Hilfsklasse um mithilfe der zlib zu packen.
 * Basiert auf dem Deflater von java.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-08, cK, Created.
 * </ul>
 *
 * @todo Strategie mit hinausliefern.
 *
 * @version $Revision: 1.3 $, $Date: 2001/08/06 16:15:04 $
 *
 * @author cK, $Author: koestlin $
 */
class IO_API Deflater {
  public:
    /// Konstante fall deflated
    static const int DEFLATED;

    /// Konstante falls nicht Komprimiert
    static const int NO_COMPRESSION;

    /// compression level moeglichst schnell
    static const int BEST_SPEED;

    /// compression level moeglichst klein
    static const int BEST_COMPRESSION;

    /// default compressionlevel
    static const int DEFAULT_COMPRESSION;

    /// packstrategie filtered
    static const int FILTERED;

    /// packstrategie huffmann
    static const int HUFFMAN_ONLY;

    /// default packstrategy
    static const int DEFAULT_STRATEGY;

    /** Erzeugt einen neuen Packer mit einem gewissen Level.
     *
     * @param level Compressionslevel.
     * @param nowrap blabla 
     */
    Deflater(int level, bool nowrap) {
      create(level, DEFAULT_STRATEGY, nowrap);
    }

    /** Erzeugt einen neuen Deflater mit einem gewissen Compressionslevel. 
     *
     * @param level Compressionslevel.
     */
    Deflater(int level) {
      create(level, DEFAULT_STRATEGY, false);
    }

    /** Erzeugt einen neuen Deflater mit default compressionslevel, 
     * strategie und wrapper.
     */
    Deflater() {
      create(DEFAULT_COMPRESSION, DEFAULT_STRATEGY, false);
    }
 
    /** Raeumt auf. */
    virtual ~Deflater() {
	    if (stream != 0) {
        int res = ::deflateEnd(stream);
        if (res == Z_STREAM_ERROR) {
          throw(Exception("Deflater::end - ZLIB - deflateEnd error", 
                          __FILE__, __LINE__));
        }
        free(stream);
        stream = 0;
	    }
    }
  
    /** Setzt neue InputDaten.
     * Sollte aufgerufen werden, wenn needsInput true liefert.
     *
     * @param buffer Datenpuffer (bleibt im Besitz des callers).
     * @param off Offset in die Daten.
     * @param len Anzahl von Bytes.
     */
    void setInput(DataBuffer* buffer, int off, int len) {
      if (buffer == 0) {
        throw(Exception("Deflater::setInput - buffer == 0", 
                        __FILE__, __LINE__));
      }
      if ((off < 0) || (len < 0) || (off + len > buffer->getSize())) {
        throw(Exception("Deflater::setInput - arrayindexoutofbounds", 
                        __FILE__, __LINE__));
      }
      Deflater::buf = buffer;
      Deflater::off = off;
      Deflater::len = len;
    }

    /** Setzt neue InputDaten.
     * Siehe setInput(DataBuffer, int, int).
     *
     * @param buffer Neue Daten.
     */
    void setInput(DataBuffer* buffer) {
	    setInput(buffer, 0, buffer->getSize());
    }


//    void setStrategy(int strategy) {
//      if (strategy != DEFAULT_STRATEGY &&
//          strategy != FILTERED &&
//          strategy != HUFFMAN_ONLY) {
//        throw(Exception("Deflater::setStrategy - illegalArgument"));
//      }
//      if (Deflater::strategy != strategy) {
//        Deflater::strategy = strategy;
//        setParams = true;
//	    }
//    }


//    void setLevel(int level) {
//	    if (((level < 0) || (level > 9)) && (level != DEFAULT_COMPRESSION)) {
//        throw(Exception("Deflater::setLevel - illegalargument"));
//	    }
//      if (Deflater::level != level) {
//        Deflater::level = level;
//        setParams = true;
//	    }
//    }

    /** Muessen neue Daten zur Compression geliefert werden. 
     *
     * @return true falls keine Daten zur Compression mehr vorliegen.
     */
    bool needsInput() {
	    return len <= 0;
    }

    /** Fordert den Deflater auf, die Kompression abzuschliessen.
     */
    void pleaseFinish() {
	    finish = true;
    }

    /** Ist die Kompression abgeschlossen.
     *
     * @return true Kompression vollstaendig.
     */
    bool isFinished() {
  	  return finished;
    }

    /** Packt Daten.
     *
     * @param buffer Daten.
     * @param off Offset in die Daten.
     * @param len Anzahl von Byte.
     */
    int deflate(DataBuffer* buffer, int off, int len) {
	    if (buffer == 0) {
        throw(Exception("Deflater::deflate - nullpointerexception", 
                        __FILE__, __LINE__));
	    }
	    if ((off < 0) || (len < 0) || (off + len > buffer->getSize())) {
        throw(Exception("Deflater::deflate - ArrayIndexOutOfBoundsException", 
                        __FILE__, __LINE__));
	    }
	    return deflateBytes(buffer, off, len);
    }

    /** Packt Daten (siehe deflate(DataBuffer, int, int)).
     *
     * @param buffer Daten.
     */
    int deflate(DataBuffer* buffer) {
	    return deflate(buffer, 0, buffer->getSize());
    }

    /** Liefert die Adler-checksumme.
     *
     * @return int Adlerchecksumme.
     */
    int getAdler() {
	    if (stream == 0) {
        throw(Exception("Deflater::getAdler - nullpointer", 
                        __FILE__, __LINE__));
	    }
	    return stream->adler;
    }

    /** Liefert die Anzahl total komprimierter Byte.
     *
     * @return int Anzahl originalBytes.
     */
    int getTotalIn() {
	    if (stream == 0) {
        throw(Exception("Deflater::getTotalIn - nullpointer", __FILE__, __LINE__));
	    }
	    return stream->total_in;
    }

    /** Liefert die Anzahl der komprimierten Bytes.
     *
     * @return int Anzahl komprimierter Byte.
     */
    int getTotalOut() {
      if (stream == 0) {
        throw(Exception("Deflater::getTotalOut - nullpointer", 
                        __FILE__, __LINE__));
      }
      return stream->total_out;
    }


    /** Resetiert die Kompression.
     */
    void reset() {
	    if (stream == 0) {
        throw(Exception("Deflater::reset - nullpointer", 
                        __FILE__, __LINE__));
	    }
      int res = deflateReset(stream);
      if (res != Z_OK) {
        throw(Exception("Deflater::reset - ZLIB - deflateReset error", 
                        __FILE__, __LINE__));
      }
	    finish = false;
	    finished = false;
	    off = 0;
      len = 0;
    }

    /** Initialisiert die Kompression. 
     *
     * @param level Compressionslevel.
     * @param strategy Compressionsstrategie.
     * @param nowrap Wrap.
     */
    void init(int level, int strategy, bool nowrap) {
      stream = (z_stream*)calloc(1, sizeof(z_stream));
      if (stream == 0) {
        throw(Exception("Deflater::init - OutOfMemory", 
                        __FILE__, __LINE__));
      } else {
        switch (::deflateInit2(stream, level, Z_DEFLATED, 
                               nowrap ? -MAX_WBITS : MAX_WBITS, 
                               8, strategy)) {
          case Z_OK:
            return;
          case Z_MEM_ERROR:
            free(stream);
            stream = 0;
            throw(Exception("Deflater::init - out of memory 2", 
                            __FILE__, __LINE__));
          case Z_STREAM_ERROR:
            free(stream);
            stream = 0;
            throw(Exception("Deflater::init - stream error", 
                            __FILE__, __LINE__));
          default:
            std::cout << "Deflater::init - Error : " << stream->msg << std::endl;
            free(stream);
            stream = 0;
            throw(Exception("Deflater::init - internal error", 
                            __FILE__, __LINE__));
        }
      }
    }

    /** Setzt das Dictionary. siehe (setDictionary(DataBuffer, int, int)
     *
     * @param buffer Daten.
     */
    void setDictionary(DataBuffer* buffer) {
      setDictionary(buffer, 0, buffer->getSize());
    }

    /** Setzt das Dictionary.
     *
     * @param buffer Daten.
     * @param off Offset in die Daten.
     * @param len Anzahl von Byte.
     */
    void setDictionary(DataBuffer* buffer, int off, int len) {
	    if ((stream == 0) || (buffer == 0)) {
        throw(Exception("Deflater::setDictionary - stream oder buffer == 0", 
                        __FILE__, __LINE__));
	    }
      if ((off < 0) || (len < 0) || (off + len > buffer->getSize())) {
        throw(Exception("Deflater::setDictionary - arrayindexoutofbounds", 
                        __FILE__, __LINE__));
	    }

      int res = ::deflateSetDictionary(stream, (Bytef*)buffer->getData(off), len);
      switch (res) {
        case Z_OK:
          break;
        case Z_STREAM_ERROR:
          throw(Exception("Deflater::setDictionary - illegal argument", 
                          __FILE__, __LINE__));
        default:
          throw(Exception("Deflater::setDictionary - internal error", 
                          __FILE__, __LINE__));
      }
    }


  private:
    /** Zlibstream. */
    z_stream* stream;

    /** Verwendeter Datenpuffer. */
    DataBuffer* buf;

    /** Offset in den Datenpuffer. */
    int off;

    /** Anzahl zu komprimierender Byte. */
    int len;

    /** Level der zur kompression verwendet werden soll. */
    int level;

    /** Gewuenschte Kompressionsstrategie. */
    int strategy;

    /** Sollen die deflateParameter initialisiert werden. */
    bool setParams;

    /** Soll die Kompression abgeschlossen werden. */
    bool finish;

    /** Ist die Kompression fertig. */
    bool finished;
    
    /** Hilfsmethode, um die Attribute richtig zu initialisieren.,
     *
     * @param _level Compressionslevel.
     * @param _strategy Compressionsstrategy.
     * @param _nowrap Wrapped.
     */
    void create(int _level, int _strategy, bool _nowrap) {
      off = 0;
      len = 0;
      setParams = false;
      finish = false;
      finished = false;
      buf = 0;

      level = _level;
      strategy = _strategy;
      init(level, strategy, _nowrap);

    }

    /** Packt mithilfe der zlib.
     *
     * @param buffer Datenpuffer, der gepackt werden soll.
     * @param off Offset in die Daten.
     * @param len Anzahl der Daten.
     */
    int deflateBytes(DataBuffer* buffer, int off, int len) {
      if (stream == 0) {
        throw(Exception("Deflater::deflateBytes - stream == 0", 
                        __FILE__, __LINE__));
      } else {
        DataBuffer* inBuffer = buf;
        DataBuffer* outBuffer = buffer;
        if (inBuffer == 0) {
          return(0);
        }
        if (outBuffer == 0) {
          return(0);
        }

        if (setParams == true) {
          // deflate set deflation parameter
          stream->next_in = (Bytef*)inBuffer->getData(Deflater::off);
          stream->next_out = (Bytef*)outBuffer->getData(off);
          stream->avail_in = Deflater::len;
          stream->avail_out = len;
          int res = ::deflateParams(stream, level, strategy);
          switch (res) {
            case Z_OK:
              setParams = false;
              Deflater::off += Deflater::len - stream->avail_in;
              Deflater::len = stream->avail_in;
              return(len - stream->avail_out);
            case Z_BUF_ERROR:
              setParams = false;
              return(0);
            default:
              throw(Exception("Deflater::deflateBytes - internal error", 
                              __FILE__, __LINE__));
          }
        } else {
          // deflate
          stream->avail_in = Deflater::len;
          stream->avail_out = len;
          if (stream->avail_in > 0) {
            stream->next_in = (Bytef*)inBuffer->getData(Deflater::off);
          }
          if (stream->avail_out > 0) {
            stream->next_out = (Bytef*)outBuffer->getData(off);
          }

          int res = ::deflate(stream, finish ? Z_FINISH : Z_NO_FLUSH);
          switch (res) {
            case Z_STREAM_END:
              finished = true;
            case Z_OK:
              Deflater::off += Deflater::len - stream->avail_in;
              Deflater::len = stream->avail_in;
              return(len - stream->avail_out);
            case Z_BUF_ERROR:
              return(0);
            default:
              std::cout << "InternalError - " << stream->msg << std::endl;
              throw(Exception("Deflater::deflate - internal error", 
                              __FILE__, __LINE__));
          }
        }
      }
    }
};

#endif // _Deflater_h_
