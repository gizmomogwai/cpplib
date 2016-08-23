#pragma once

#include <lang/DataBuffer.h>
#include <lang/Long.h>

#include <io/DataInputStream.h>
#include <io/FilterInputStream.h>
#include <io/IOException.h>

#include <iostream>
#include <cassert>

/** Inputstream, der das Chunken eines HTTPServers verbirgt.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-02-15, cKtS, Created.
 *   <li> 2001-03-31, cK, throw clausel besser beachtet (linux)
 * </ul>
 *
 * @author cKtS, $Author: koestlin $
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:32 $
 */
class ChunkedHTTPInputStream : public FilterInputStream {

  public:
    /** ChunkedHTTPInputStream.
     *
     * @param inputStream Stream der gefiltert werden soll.
     */
    ChunkedHTTPInputStream(InputStream* _in) 
      : FilterInputStream(_in, false), dataSize(-1) {
    }

    /** Raeumt auf. */
    virtual ~ChunkedHTTPInputStream() {
    }

    int read() throw (IOException) {
      handleChunk();

      if (dataSize == 0) {
        handleFooter();
        return(-1);
      } else {
        int res = in->read();

        dataSize--;
        clipDataSize();
        
        return(res);
      }
    }

    int read(DataBuffer& _buffer, int _offset, int _length) 
      throw (IOException) {
      handleChunk();

      if (dataSize == 0) {
        handleFooter();
        return(-1);
      } else {
        int minLength = (_length < dataSize) ? _length : dataSize;
        int res = in->read(_buffer, _offset, minLength);
      
        dataSize -= res;
        clipDataSize();

        return(res);
      }
    }

  private:
    /** Gibt die Anzahl noch lesbarer Daten an. 
     * -1 falls chunkSize ausgelesen werden muss. 
     * 0 falls keine Daten mehr kommen.
     */
    int dataSize;

    /** Behandelt, falls noetig eine Chunklinie. */
    void handleChunk() {
      if (dataSize == -1) {
        DataInputStream dIn(in, false);
        
	std::auto_ptr<std::string> chunkSize = dIn.readLine();
	assert(chunkSize.get());
        dataSize = Long::parseLong(*chunkSize, 16);
      }
    }

    /** Behandelt den Footer. */
    void handleFooter() throw (IOException) {

      DataInputStream dIn(in, false);
      
      std::auto_ptr<std::string> help = dIn.readLine();
      
      while ((help.get() != 0) && (help->length() != 0)) {
        help = dIn.readLine();
      }
    
    }

    /** Achtet darauf, dass dataSize, richtig gesetzt wird, und 
     * crlfs ueberlesen werden.
     */
    void clipDataSize() {
      if (dataSize == 0) {
        dataSize--;
        // crlf ueberspringen
        int red = in->read();
        red = in->read();
      }
    }

};
