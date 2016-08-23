#ifndef _ZipEncryptedInputStream_h_
#define _ZipEncryptedInputStream_h_

#include <assert.h>

#include <string>

#include <lang/ByteDataBuffer.h>
#include <io/zip/ZipCrc32.h>
#include <io/FilterInputStream.h>

/** InputStream, der Zipartige verroedelung an den start bringt.
 *
 * Die Encryption ist genau im letzen Abschnitt von
 * <a href="../../../docs/whitepaper/zip-appnote.txt">Zip-Appnote</a> 
 * beschrieben.
 * 
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-07-13, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.2 $ $Date: 2001/08/06 16:15:04 $
 *
 * @author cK $Author: koestlin $
 */
class ZipEncryptedInputStream : public FilterInputStream {

  public:
    /** Erzeugt den InputStream indem zunaechste die 
     * Encryptionkeys anhand des passworts und des
     * encryptionheaders initialisiert werden.
     *
     * @param in InputStream geht je nach handleStream in 
     *        den Besitzt von EncryptedInputStream ueber.
     * @param handelStream siehe FilterInputStream
     * @param _passwd Passwort, bleibt im Besitzt des Callers.
     * @param _crc32 Checksumme des Files um das Passwort zu 
     *        checken.
     */
	  ZipEncryptedInputStream(InputStream* in, 
													  bool handleStream, 
													  std::string* _passwd, int _crc32) 
		  : FilterInputStream(in, handleStream), 
		    passwd(_passwd), 
		    fileCRC32(_crc32) {
		  
		  if (passwd == 0) {
			  throw(Exception("file encrypted but no passwd given", 
											  __FILE__, __LINE__));
		  }

		  initializeEncryptionKeys();

		  decryptEncryptionHeader();
	  }

    /** Raeumt auf. */
	  virtual ~ZipEncryptedInputStream() {
	  }

    /** Liesst ein Byte vom unterliegenden Strom und decrypted es.
     *
     * @return int -1 falls keine Daten mehr da ansonsten den 
     *         bytewert.
     */
    int read() throw (IOException) {
		  int red = in->read();
		  if (red == -1) {
			  return(red);
		  }
		  unsigned char temp = red ^ decryptByte();
		  updateKeys(temp);
		  return(temp);
	  }

    /** Liesst eine Menge von Bytes vom unterliegenden Strom ein.
     * Momentan wird immer nur ein einzelnes Byte eingelesen.
     *
     * @param buffer Datenpuffer.
     * @param offset Offset in den Puffer.
     * @param length Anzahl zu lesender Bytes.
     *
     * @return int Anzahl gelesener Byte
     */
    int read(DataBuffer& buffer, int offset, int length) 
      throw (IOException) {

      // elegant aber vielleicht ineffizient
      char* data = (char*)buffer.getData(offset);
      int red = read();
      if (red != -1) {
        *data = red;
        return 1;
      } else {
        return red;
      }
      // korrekt aber haesslich
  //    char* data = (char*)buffer->getData(offset);
  //    int red = read();
  //    int count = 0;
  //    while ((red != -1) && (count < length)) {
  //      data[count] = red & 0xff;
  //      count++;
  //      if (count < length) {
  //        red = read();
  //      }
  //    }
  //    if (red == -1) {
  //      if (count == 0) {
  //        return(-1);
  //      } else {
  //        return(count);
  //      }
  //    } else {
  //      return(length);
  //    }

    }


  private:
    /** Rechnet den Encryptionheader in die Keys mit ein.
     *
     * Eine Exception wird geworfen, wenn die crc des files 
     * nicht stimmen kann.
     */
	  void decryptEncryptionHeader() {
		  ByteDataBuffer buffer(12);
		  unsigned char* bytes = (unsigned char *)buffer.getData();
		  int red = in->readFully(buffer);
		  assert(red == 12);

		  for (int i=0; i<12; i++) {
			  unsigned char c = bytes[i] ^ decryptByte();
			  updateKeys(c);
			  bytes[i] = c;
		  }

      // bytes[11] must be fileCRC32 (highest byte of)
      if (bytes[11] != ((fileCRC32 >> 24) & 0xff)) {
        throw(Exception("wrong passwd", __FILE__, __LINE__));
      }
	  }

    /** Decrypted ein Byte.
     *
     * @return unsigned char decryptetes byte.
     */
	  unsigned char decryptByte() {
		  unsigned short temp = (k2.getChecksum() & 0xffff ) | 2;
		  unsigned char res = (unsigned char)(((temp * (temp ^ 1)) >> 8) & 0xff);
		  return(res);
	  }

    /** Initialisiert die EncryptionKeys mit passwort.
     */
	  void initializeEncryptionKeys() {
      k0.setChecksum(0x12345678);
      k1.setChecksum(0x23456789);
      k2.setChecksum(0x34567890);

		  for (int i=0; i<(int)passwd->length(); i++) {
			  updateKeys((*passwd)[i]);
		  }
	  }

    /** Updates die Keys.
     *
     * @param newOne Neues Zeichen.
     */
	  void updateKeys(unsigned char newOne) {
      k0.update(newOne);
      
      k1.setChecksum(k1.getChecksum() + (k0.getChecksum() & 0xff));
      k1.setChecksum(k1.getChecksum() * 134775813L + 1);

      k2.update(k1.getChecksum() >> 24);
	  }

    /** Key 0. */
    ZipCrc32 k0;

    /** Key 1. */
    ZipCrc32 k1;

    /** Key 2. */
    ZipCrc32 k2;

    /** Passwort. */
	  std::string* passwd;

    /** CRC des files. */
	  unsigned int fileCRC32;

};

#endif // _ZipEncryptedInputStream_h_
