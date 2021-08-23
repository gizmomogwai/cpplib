#pragma once

#include <io/FilterInputStream.h>
#include <io/IOException.h>
#include <memory>

/** Liefert Basisdatentypen aus einem InputStream.
 *
 * Die Implementierung passt zu einem java DataOutputStream.
 * Dabei muss man hinzufuegen, dass die readLine-methode
 * mit einem PrintWriter.println kompatibel ist.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2000-11-15, cK, Created.
 *  <li> 2000-11-20, cK, Commented.
 *  <li> 2000-12-29, cK, readLine added.
 *  <li> 2001-02-14, cK, readChar, readByte und readUTF ueberarbeitet.
 *  <li> 2001-04-14, cK, read*s added.
 *  <li> 2001-06-20, cK, readLong rausgenommen, 
 *       da das sowieso nicht geht!
 * </ul>
 *
 * @version $Revision: 1.6 $, $Date: 2001/07/05 13:27:22 $
 *
 * @author ck, $Author: koestlin $
 */
class DataInputStream : public FilterInputStream {

 public:

  /** Erzeugt einen neuen DataInputStream.
   *
   * @param _in Gewrapter Stream.
   * @param _handleStream kann auf true gesetzt werden, wenn der
   *        InputStream von dem DataInputStream verwaltet werden soll.
   */
  DataInputStream(InputStream* _in, bool _handleStream);
 

  /** Gibt den Stream frei.
   *
   * Gibt auch den Uebergebenen Stream frei, falls handleStream gesetzt
   * wurde. 
   */
  virtual ~DataInputStream();

  /** Liesst 1 byte und liefert true falls != 0x00 und false falls ==
   * 0x00. 
   *
   * @return bool Bool-wert.
   *
   * @exception IOException, wenn nicht genug input vorliegt.
   */
  virtual bool readBoolean() throw (IOException);
  
  /** Liesst ein Byte. 
   *
   * @return unsigned char das byte.
   *
   * @exception IOException, wenn nicht genug input vorliegt.
   */
  virtual unsigned char readByte() throw (IOException);
  
  /** Liesst ein Char ein.
   *
   * @return char der charachter.
   *
   * @exception IOException, wenn nciht genug input vorliegt.
   */
  virtual char readChar() throw (IOException);
  
  /** Liesst ein Double (8byte).
   *
   * @return double Double-Wert.
	 *
	 * @exception IOException, wenn nicht genug input vorliegt.
   */
  virtual double readDouble() throw (IOException);
  
  /** Liesst ein Float (4byte).
   *
   * @return float Float-Wert.
	 *
	 * @exception IOException, wenn nicht genug input vorliegt.
   */
  virtual float readFloat() throw (IOException);
  
  /** Liesst eine Menge von Floats ein.
   *
   * @param data Speicherbereich.
   * @param nOfFloats Anzahl von zu lesenden Floats.
   *
   * @exception IOException falls nicht genug daten anliegen oder anderes.
   */
  virtual void readFloats(float* data, int nOfFloats) throw (IOException);
  
  /** Liesst ein Int (4byte).
   *
   * @return int Integer-Wert.
	 *
	 * @exception IOException, wenn nicht genug input vorliegt.
   */
  virtual int readInt() throw (IOException);

	/** Liesst eine Menge von Ints ein.
	 *
	 * @param data Speicherbereich.
	 * @param nOfInts Anzahl von zu lesenden Ints.
	 *
	 * @exception IOException falls nicht genug Daten anliegen.
	 */
	virtual void readInts(int* data, int nOfInts) throw (IOException);

  /** Liesst ein Short (2 byte).
   *
   * @return short int
	 *
	 * @exception IOException, wenn nicht genug input vorliegt.
   */
  virtual short int readShort() throw (IOException);

  /** Liesst eine Menge von Shorts ein.
   *
   * @param data Speicherbereich.
   * @param nOfShorts Anzahl von zu lesenden Shorts.
   *
   * @exception IOException falls nicht genug daten anliegen.
   */
  virtual void readShorts(short* data, int nrOfShorts) throw (IOException);
  
  /** Liesst ein unsigned Short (2 byte).
   *
   * @return unsigned short int
	 *
	 * @exception IOException, wenn nicht genug input vorliegt.
   */
  virtual unsigned short int readUnsignedShort() throw (IOException);

  /** Liesst eine Menge von unsigned shorts ein.
   *
   * @param data Speicherbereicht.
   * @param nOfShorts Anzahl von einzulesenden unsigned shorts.
   *
   * @exception IOException falls nicht genug daten anliegen.
   */
  virtual void readUnsignedShorts(unsigned short* data, int nrOfShorts) throw (IOException) {
    readShorts((short*)data, nrOfShorts);
  }
  
  /** Liesst eine Zeile ein.
   *
   * Eine Zeile wird durch 0x0D, oder 0x0D0x0A beendet. Weder das 
   * eine noch das andere wird zurueckgeliefert.
   *
   * Wird nur ein '\n' gelesen wird ein leerer String geliefert.
   * Fuehrende '\r' werden ignoriert.
   *
   * @return std::string* Zeile oder 0 fall eof.
   */
  virtual std::unique_ptr<std::string> readLine() throw (IOException);

  /** Liesst einen UTF-String. Ein UTFString ist ein chararray, 
   * bei dem zunaechst steht, wieviele chars das chararray umfasst.
   * Das ist als unsigned short codiert.
   *
   * @return char* String. muss mit delete[] befreit werden.
   */
  virtual char* readUTF() throw (IOException);

  /** Liesst einen UTFString. siehe readUTF.
   *
   * Liefert einen std::string zurueck oder eben eine Exception.
   *
   * @return std::string String.
   */
  virtual std::string readUTFString() throw (IOException);

//	/** Liesst eine Long(8byte) ein.
//	 *
//	 * @return long Long.
//	 */
//  virtual long readLong() throw (IOException);

 private:
	/** Convertiert die Order eines ganzen Speicherblocks von 32bit-Werten
	 * (ints oder floats).
	 *
	 * @param values Werte.
	 * @param nOfValues Anzahl von Werten.
	 */
	void convert32bitValues(void* values, int nOfValues) {
		unsigned char* help = (unsigned char*)values;
		for (int i=0; i<nOfValues; i++) {
			unsigned char h;
			h = help[0];
			help[0] = help[3];
			help[3] = h;
    
			h = help[1];
			help[1] = help[2];
			help[2] = h;

			help += 4;
		}
	}

	/** Convertier die Order eines ganzen Speicherblocks von 16bit-Werten
	 * (shorts).
	 *
	 * @param values Werte.
	 * @param nOfValues Anzahl von Werten.
	 */
	void convert16bitValues(void* values, int nOfValues) {
		unsigned char* help = (unsigned char*)values;
		for (int i=0; i<nOfValues; i++) {
			unsigned char h = help[0];
			help[0] = help[1];
			help[1] = h;

			help += 2;
		}
	}

	/** Convertiert die Order eines ganzen Speicherblocks von 64bit Werten.
	 * (long oder doulbes).
	 *
	 * @param values Werte.
	 * @param nOfValues Anzahl von Werten.
	 */
	void convert64bitValues(void* values, int nOfValues) {
		unsigned char* help = (unsigned char*)values;
		for (int i=0; i<nOfValues; i++) {
			unsigned char h = help[0];
			help[0] = help[7];
			help[7] = h;

			h = help[1];
			help[1] = help[6];
			help[6] = h;

			h = help[2];
			help[2] = help[5];
			help[5] = h;

			h = help[3];
			help[3] = help[4];
			help[4] = h;

			help += 8;
		}
	}
};
