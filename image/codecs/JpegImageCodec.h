#ifndef _JpegImageCodec_h_
#define _JpegImageCodec_h_

#include <image/ImageApi.h>

#include <stdio.h>
#include <iostream>

extern "C" {
  // von freeimage abgeschrieben
  //#define XMD_H
  //#undef FAR
  #include <jpeglib.h>
}

#include <image/codecs/ImageCodec.h>

#include <lang/DataBuffer.h>
#include <io/OutputStream.h>

/** Liesst jpgs mithilfe der libjpeg.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-30, cK, Created.
 *   <li> 2000-12-30, cK, fall mit in der mitte gesplittetem
 *        jpg durchgespielt. und dabei problem mit der default
 *        errorbehandlung gefunden.
 *   <li> 2001-01-03, cK, ein paar mehr exceptions eingebaut
 *   <li> 2001-04-12, cK, Errorhandling eingebaut
 *        (damit exception geworfen wird, falls nicht jpeg vorliegt).
 * </ul>
 *
 * @todo bei read und write muessen die jpeg-lib structuren
 *       richtig aufgeraeumt werden.
 *
 * @version $Revision: 1.5 $, $Date: 2001/10/23 11:25:02 $
 *
 * @author cK, $Author: schaefer $
 */
class IMAGE_API JpegImageCodec : public ImageCodec {

  public:

    /** Erzeugt einen neuen JPEGImageCodec.
     *
     * @param _vFlip Falg, das angibt, ob beim
     *        schreiben und lesen die Daten vertical gespiegelt werden
     *        sollen.
     * @param _quality Encodierungsqualitaet in Prozent. vFlip default auf false.
     */
    JpegImageCodec(bool _vFlip, int _quality) :
      vFlip(_vFlip),
      quality(_quality) {
    }

    /** Erzeugt einen neuen JPEGImageCodec.
     *
     * @param _vFlip Falg, das angibt, ob beim
     *        schreiben und lesen die Daten vertical gespiegelt werden
     *        sollen.
     */
    JpegImageCodec(bool _vFlip = false) :
      vFlip(_vFlip),
      quality(60) {
    }

    /** Erzeugt einen neuen JPEGImageCodec.
     *
     * @param _quality Encodierungsqualitaet in Prozent. vFlip default auf false.
     */
    JpegImageCodec(int _quality) :
      vFlip(false),
      quality(_quality) {
    }


    /** Raeumt auf. */
    virtual ~JpegImageCodec() {
    }


    void write(Image* _image, OutputStream* _out) throw (Exception);


    Image* read(InputStream* _in) throw (Exception);

  private:
    /** Initialisiert die Fehlerbehandlung.
     *
     * Das mit dem returnparameter ist zwar unschoen, aber
     * so ist die speicherverwaltung einfacher.
     *
     * @param jErr returnparameter.
     */
    void initErrorHandler(struct jpeg_error_mgr* jErr);


    /** Statische Hilfsmethode, die von der jpeg_source_mgr Struktur
     * benoetigt wird.
     *
     * @param cInfo das Lib-jpeg-objekt.
     */
    static void initSourceFN(j_decompress_ptr cInfo) {
    }


    /** Besser hier definieren, da es in meinem Testprojekt sonst
     * zu abstuerzen, wahrscheinlich im context mit windows gekommen ist,
     * die defaultimplementierung versucht das aktuell aktive Fenster zu
     * bekommen. und wenn man kein fenster hat geht das nicht.
     *
     * @param cInfo das Lib-jpeg-objekt.
     */
    static void outputMessageFN(j_common_ptr cInfo);


    /** Callback falls in der Jpeglib ein Fehler auftrat.
     *
     * @param cInfo das Lib-jpeg-objekt.
     */
    static void errorExitFN(j_common_ptr cInfo);


    /** Statische Hilfsmethode, die von der jpeg_source_mgr-structur
     * benoetigt wird.
     *
     * @param cInfo das Lib-Jpeg-Object.
     */
    static boolean fillInputBufferFN(j_decompress_ptr cInfo) {
      JpegImageCodec* codec = (JpegImageCodec*)(cInfo->client_data);
      boolean res = codec->fillInputBuffer(cInfo);
      return(res);
    }


    /** Statische Hilfsmethode, die von der jpeg_source_mgr-structur
     * benoetigt wird.
     *
     * @param cInfo das Lib-Jpeg-Object.
     * @param l anzahl von byte, die uebersprungen werden sollen.
     */
    static void skipInputDataFN(j_decompress_ptr cInfo, long l) {
      JpegImageCodec* codec = (JpegImageCodec*)(cInfo->client_data);
      codec->skipInputData(cInfo, l);
    }


    /** resync keine ahnung.
     *
     * Kann glaube ich fuer streams nicht implementiert werden.
     *
     * @param cInfo das lib-jpeg-objekt.
     * @param desired keine ahnung.
     */
    static boolean resyncToRestartFN(j_decompress_ptr cInfo, int desired) {
      return FALSE;
    }


    /** beendet die sourcedecompression.
     *
     * @param cInfo das lib-jpeg-objekt.
     */
    static void termSourceFN(j_decompress_ptr cInfo) {
//      std::cout << "JpegImageCodec::termSourceFN" << std::endl;
    }


    /** Fuellt den localen Puffer mit etwas Daten.
     *
     * das lib-jpeg-object muss geupdatet werden, je nachdem welche
     * anzahl von byte gelesen wurden.
     *
     * @param cInfo das lib-jpeg-object.
     *
     * @return boolean TRUE, falls werte gelesen wurden.
     */
    boolean fillInputBuffer(j_decompress_ptr cInfo);


    /** Ueberspringt eine menge von byte.
     *
     * das lib-jpeg-object muss angepasst werden.
     *
     * @param cInfo das lib-jpeg-object.
     * @param l anzahl zu ueberspringender byte.
     */
    void skipInputData(j_decompress_ptr cInfo, long l) {
      if (l > 0) {
        while (l > (long)(cInfo->src->bytes_in_buffer)) {
          l -= (long)(cInfo->src->bytes_in_buffer);
          fillInputBuffer(cInfo);
        }
        cInfo->src->next_input_byte += l;
        cInfo->src->bytes_in_buffer -= l;
      }
    }


    /** statische hilfsmethode, die den outputbuffer initialisiert und die
     * werte next_output_byte und free_in_buffer setzt.
     *
     * @param cInfo jpeg-lib-object.
     */
    static void initDestinationFN(j_compress_ptr cInfo) {
      JpegImageCodec* codec = (JpegImageCodec*)(cInfo->client_data);
      codec->initDestination(cInfo);
    }


    /** eigentlich implementierung.
     *
     * @param cInfo jpeg-lib-object.
     */
    void initDestination(j_compress_ptr cInfo) {
      cInfo->dest->next_output_byte = (unsigned char*)buffer->getData();
      cInfo->dest->free_in_buffer = buffer->getSize();
    }


    /** statische hilfsmethode, die den outputbuffer ganz schreiben soll.
     *
     * @param cInfo jpeg-lib-object.
     */
    static boolean emptyOutputBufferFN(j_compress_ptr cInfo) {
      JpegImageCodec* codec = (JpegImageCodec*)(cInfo->client_data);
      boolean res = codec->emptyOutputBuffer(cInfo);
      return res;
    }


    /** Eigentliche Implementierung.
     *
     * @param cInfo jpeg-lib-object.
     */
    boolean emptyOutputBuffer(j_compress_ptr cInfo) {
      out->write(buffer);
      initDestination(cInfo);
      return TRUE;
    }


    /** Beendet die ausgabe.
     * muss noch den rest, der im buffer gesetzt ist schreiben.
     *
     * @param cInfo jpeg-lib-object.
     */
    static void termDestinationFN(j_compress_ptr cInfo) {
      JpegImageCodec* codec = (JpegImageCodec*)(cInfo->client_data);
      codec->termDestination(cInfo);
    }


    /** Eigentliche Implementierung.
     *
     * @param cInfo jpeg-lib-object.
     */
    void termDestination(j_compress_ptr cInfo) {
      int l = buffer->getSize() - cInfo->dest->free_in_buffer;
      out->write(buffer, 0, l);
    }


    /** Eingabestrom. nur bei read gesetzt. */
    InputStream* in;


    /** Ausgabestrom, nur bei write gesetzt. */
    OutputStream* out;

    /** interner lesebuffer fuer daten. */
    DataBuffer* buffer;

    /** Sollen die Daten beim schrebien gespiegelt werden. */
    bool vFlip;

    /** Qualitaet mit der encodiert wird */
    int quality;

};

#endif // _JpegImageCodec_h_
