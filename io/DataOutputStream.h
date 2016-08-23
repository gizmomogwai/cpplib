#pragma once

#include <io/FilterOutputStream.h>
#include <io/IOException.h>

/** Schreibt Basisdatentypen in einen OutputStream.
 *
 * Dabei wird ein Java-maessiger OutputStrom zugrundegelegt.
 * Byteorder etc... Zusaetzlich wird eine stringmaessige Operation
 * angeboten. Diese arbeitet aber nicht mit unicodesachen. macht einiges um
 * das 0x0d 0x0a problem zu loesen.
 * 
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2000-12-06, cK, Commented.
 *  <li> 2001-04-13, cK, Um write*s erweitert.
 * </ul>
 *
 * @todo writeString in Writer auslagern.
 *
 * @version $Revision: 1.2 $, $Date: 2001/09/13 13:11:10 $
 *
 * @author ck, $Author: koestlin $
 */
class DataOutputStream : public FilterOutputStream {
  
 public:
  /** Erzeugt einen neuen DataOutputStream.
   *
   * @param _in Gewrapter Stream.
   * @param _handleStream kann auf true gesetzt werden,
   *    wenn der InputStream von dem DataInputStream verwaltet werden soll.
   */
  DataOutputStream(OutputStream* _in, bool _handleStream);
  
  /** Gibt den Stream frei.
   *
   * Gibt auch den Uebergebenen Stream frei, falls handleStream gesetzt
	 * wurde. 
   */
  virtual ~DataOutputStream();
  
  /** Schreibt ein byte. 0x01 fuer true, 0x00 fuer false.
   *
   * @param v Bool-wert.
   *
   * @exception IOException wenn etwas schiefgeht.
   */
  virtual void writeBoolean(bool v) throw (IOException);
  
  /** Schreibt ein Byte. 
   *
   * @param v Wert.
   *
   * @exception IOException wenn etwas schiefgeht.
   */
  virtual void writeByte(unsigned char v) throw (IOException);

  /** Schreibt eine Menge von Byte.
   *
   * @param data Array von Charakters.
   * @param length Anzahl von Daten.
   * 
   * @exception IOException wenn etwas schiefgeht.
   */
  virtual void writeBytes(unsigned char* data, int length) throw (IOException);
  
  /** Schreibt ein Double (8byte).
   *
   * @param double Double-Wert.
   *
   * @exception IOException wenn etwas schiefgeht.
   */
  virtual void writeDouble(double v) throw (IOException);

  /** Schreibt eine Menge von doubles.
   *
   * @param data Array von Doubles.
   * @param nOfDoubles Anzahl von doubles.
   *
   * @exception IOException falls was schief geht.
   */
  virtual void writeDoubles(double* data, int nOfDoubles) throw (IOException);
  
  /** Schreibt ein Float (4byte).
   *
   * @param float Float-Wert.
   *
   * @exception IOException wenn etwas schiefgeht.
   */
  virtual void writeFloat(float v) throw (IOException);

  /** Schreibt eine Menge von Floats.
   *
   * @param data Array mit floats.
   * @param nOfFloats Anzahl von Floats.
   *
   * @exception IOException wenn was schiefgeht.
   */
  virtual void writeFloats(float* data, int nOfFloats) throw (IOException);
  
  /** Schreibt ein Int (4byte).
   *
   * @param int Integer-Wert.
   *
   * @exception IOException wenn etwas schiefgeht.
   */
  virtual void writeInt(int v) throw (IOException);

  /** Schreibt eine Menge von Ints.
   *
   * @param data Array von ints.
   * @param nOfInts Anzahl von ints.
   *
   * @exception IOException wenn etwas schief geht.
   */
  virtual void writeInts(int* data, int nOfInts) throw (IOException);

  /** Schreibt ein Short (2byte).
   *
   * @param v Short-Wert.
   *
   * @exception IOException wenn was schiefgeht.
   */
  virtual void writeShort(short v) throw (IOException);

  /** Schreibt eine Menge von Shorts.
   *
   * @param data Array von Shorts.
   * @param nOfShorts Anzahl von Shorts.
   *
   * @exception IOException falls etwas schief geht.
   */
  virtual void writeShorts(short* data, int nOfShorts) throw (IOException);

  /** Schreibt ein vorzeichenloses short (2byte).
   *
   * @param v unsigned short wert.
   *
   * @exception IOException wenn was schiefgeht.
   */
  virtual void writeUnsignedShort(unsigned short v) throw (IOException);

  /** Schreibt eine Menge von unsigned shorts.
   *
   * @param data Array von unsigned shorts.
   * @param nOfUnsignedShorts Anzahl von unsigned shorts.
   *
   * @exception IOExeption wenn etwas schief geht.
   */
  virtual void writeUnsignedShorts(unsigned short* data, 
                                   int nOfUnsignedShorts) throw (IOException);
  
  /** Schreibt einen String. 
   *
   * @param s String.
   *
   * @exception IOException wenn etwas schiefgeht.
   */
  virtual void writeString(std::string* s) throw (IOException);
  
  /** Fuegt einen Zeilenwechsel ein.
   *
   * '\n' wird als Zeilentrenner verwendet.
   *
   * @exception IOException wenn etwas schiefgeht.
   */
  virtual void writeLine() throw (IOException);

  /** Schreibt einen String als UTFstring.
   *
   * Siehe DataInputStream readUTFString.
   *
   * @param s String.
   */
  virtual void writeUTFString(std::string* s) throw (IOException);
  
};
