#ifndef Inflater_h_
#define Inflater_h_

#include <lang/DataBuffer.h>
#include <zlib.h>

/** Eigentlicher Entpacker.
 *
 * Beruht auf der zlib ... und den schoenen java-sourcen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-16, cK, Created.
 *   <li> 2000-11-20, cK, Commented.
 * </ul>
 *
 * @todo wenn man wirklich einen guten ZippedInputStream haben will, sollte
 *       man den Inflater allgemein halten und diesen hier zu einem
 *       GZIPInflater umbauen.
 *
 * @version $Revision: 1.2 $, $Date: 2001/07/16 09:58:52 $
 *
 * @author cK, $Author: koestlin $
 */
class Inflater {

  public:
    /** Erzeugt einen neuen Inflater. 
     *
     * @param _noWrap true falls man gzip-kompatibel sein will.
     */
    Inflater(bool _noWrap);

    /** Erzeugt einen neuen Inflater (mit defaultnoWrap == false). */
    Inflater();

    /** Raeumt auf. */
    virtual ~Inflater();

    /** Setzt den sourcePuffer fuer zu dekomprimierende Daten. 
     *
     * @param _sourceBuffer Puffer mit komprimierten Daten.
     * @param _sourceOffset Offset in die Daten.
     * @param _sourceLength Laenge der Daten.
     */
    void setInput(DataBuffer* _sourceBuffer, int _sourceOffset, 
									int _sourceLength);

    /** Entpackt Daten vom sourcepuffer in den targetpuffer.
     *
     * @param _targetBuffer Ziel.
     * @param _targetOffset Offset in das Ziel.
     * @param _targetLength Maximallaenge der entpackten daten.
     *
     * @return int Anzahl von dekomprimierten Byte
     */
    int inflate(DataBuffer* _targetBuffer, int _targetOffset, 
								int _targetLength);
    
    /** Fertig mit Entpacken. 
     *
     * @return bool true falls das Ende des Compressionsstroms erreicht
		 *         ist. 
     */
    bool isFinished() {
      return(finished);
    }

    /** Liefert true falls ein preset-Dictionary zu decompression benoetigt
		 * wird. 
     *
     * @return bool true falls ein dictionary benoetigt wird.
     */
    bool needsDictionary() {
      return(needDict);
    }

    /** Werden neue InputDaten benoetigt.
     *
     * @return bool true falls der SourcePuffer aufgebracuht ist.
     */
    bool needsInput();

    /** Liefert, wieviele Bytes noch im Sourcepuffer sind.
     *
     * @return int Anzahl von bytes im sourcepuffer.
     */
    int getRemaining() {
      return(sourceLength);
    }

    /** Liefert wieviele Byte bisher entpackt wurden.
     *
     * @return long Anzahl entpackter byte. 
     */
    long getTotalOut();

  private:
    /** Initialisiert die dekompression. */
    void init(bool _noWrap);
	
    /** Quelldaten fuer die Dekompression. */
    DataBuffer* sourceBuffer;

    /** Offset, ab dem die SourceDaten im Puffer stehen. */
    int sourceOffset;

    /** Anzahl der QuellDaten. */
    int sourceLength;

    /** true falls fertig. */
    bool finished;

    /** true falls ein dictionary benoetigt wird. */
    bool needDict;

    /** zlib-dekompressionszustand. */
    z_stream* stream;

};

#endif // _Inflater_h_
