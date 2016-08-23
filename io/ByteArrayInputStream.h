#pragma once

#include <io/InputStream.h>

/** Klasse um auf einem Seicherbereich mit einem InputStream abzugehen.
 *
 * Es wird nur eine Referenz auf den Speicher gespeichert,
 * nicht der Speicher des Buffers kopiert. Der Speicher wird auch nicht vom
 * Stream verwaltet. Wenn man den Speicher nicht mehr braucht muss dieser
 * also von der Applikation geloescht werden. Wird der Speicher geloescht,
 * und weiterhin auf dem Stream abgegangen droht gefahr (der stream kann
 * den speicher nicht wirklich freigeben, da er nicht weiss, was es fuer
 * ein speicher ist)
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-19, cK, Created.
 * </ul>
 *
 * @todo Bessere Rangechecks.
 *
 * @version $Revision: 1.3 $, $Date: 2001/09/13 13:11:10 $
 *
 * @author cK, $Author: koestlin $
 */
class ByteArrayInputStream : public InputStream {
  
 public:
  /** Erzeugt einen neuen ByteArrayInputStream auf dem angegebenen
	 * Speicherbereich.
   *
   * @param _buffer Source-speicher.
   * @param _offset Offset ab dem die Daten als InputStreasmangeboten
	 *        werden sollen. 
   * @param _available Anzahl der Bte, die im Strom angeboten werden
	 *        sollen. 
   */
  ByteArrayInputStream(DataBuffer* _buffer, int _offset, int _available);
  
  /** Raeumt auf.
   */
  virtual ~ByteArrayInputStream();
  
  /** Liesst ein byte aus dem strom.
   *
   * @return int byte oder -1.
   */
  virtual int read() throw (IOException);
  
  /** Liesst eine Menge von byte aus dem strom.
   *
   * @param target Datenpuffer in den die Werte geschrieben werden sollen.
   * @param offset Offset ab dem in die Daten geschrieben werden soll.
   * @param length Maximale Anzahl zu schreibender Daten.
   *
   * @return int Anzahl geschriebener byte.
   */
  virtual int read(DataBuffer& target, int offset, int length) 
    throw (IOException);
  
 private:
  /** Adresse des source-speichers. */
  unsigned char* buffer;
  
  /** Anzahl von verfuegbaren bytes. */
  int available;
  
};
