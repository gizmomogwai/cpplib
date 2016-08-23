#pragma once

#include <io/DataInputStream.h>

#include <lang/DataBuffer.h>



/** DataInputStream, der von Daten in LittleEndianess ausgeht.
 *
 * Auf intels kann dadurch das einlesen schneller geschehen!
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-13, cK, Created.
 *   <li> 2001-06-20, cK, readLong rausgenommen, 
 *        da das gar nicht ghet.
 * </ul>
 *
 * @version $Revision: 1.3 $, $Date: 2001/06/21 23:20:42 $
 *
 * @author cK, $Author: koestlin $
 */
class LittleEndianDataInputStream : public DataInputStream {
  
 public:
	/** Erzeugt einen neuen LittleEndianDataInputStream.
	 *
	 * @param _in Gewrapter Stream.
	 * @param _handleStream kann auf true gesetzt werden, wenn der
	 *        InputStream von dem DataInputStream verwaltet werden soll.
	 */
	LittleEndianDataInputStream(InputStream* _in, bool _handleStream)
		: DataInputStream(_in, _handleStream), buffer(new DataBuffer(0, 0, false)) {
	}



  

	/** Gibt den Stream frei.
	 *
	 * Gibt auch den Uebergebenen Stream frei, falls handleStream gesetzt
	 * wurde. 
	 */
	virtual ~LittleEndianDataInputStream() {
		delete(buffer);
	}



	double readDouble() throw (IOException) {
		double res;
		buffer->setData(&res, sizeof(double), false);
		int count = in->readFully(*buffer);
		if (count != sizeof(double)) {
			throw IOException("LittleEndianDataInputStream::readDouble - not enough data", 
												__FILE__, __LINE__);
		}
		return(res);
	}

	float readFloat() throw (IOException) {
		float res;
		buffer->setData(&res, sizeof(float), false);
		int count = in->readFully(*buffer);
		if (count != sizeof(float)) {
			throw IOException("LittleEndianDataInputStream::readFloat - not enough data");
		}
		return(res);
	}

	void readFloats(float* data, int nOfFloats) throw (IOException) {

		buffer->setData(data, sizeof(float) * nOfFloats, false);

		int count = in->readFully(*buffer);

		if (count != (int)(sizeof(float) * nOfFloats)) {

			throw(IOException("LittleEndianDataInputStream::readFloats - not enough data", 

												__FILE__, __LINE__));

		}

	}



	int readInt() throw (IOException) {

		int res;

		buffer->setData(&res, sizeof(int), false);

		int count = in->readFully(*buffer);

		if (count != sizeof(int)) {

			throw(IOException("LittleEndianDataInputStream::readInt - not enough data",

												__FILE__, __LINE__));

		}

		return(res);

	}





	void readInts(int* data, int nOfInts) throw (IOException) {

		buffer->setData(data, sizeof(int) * nOfInts, false);

		int count = in->readFully(*buffer);

		if (count != (int)(sizeof(int) * nOfInts)) {

			throw(IOException("LittleEndianDataInputStream::readFloats - not enough data", 

												__FILE__, __LINE__));

		}

	}



	short readShort() throw (IOException) {

		short res;

		buffer->setData(&res, sizeof(short), false);

		int count = in->readFully(*buffer);

		if (count != (int)(sizeof(short))) {

			throw(IOException("LittleEndianDataInputStream::readShort - not enough data", 

												__FILE__, __LINE__));

		}

		return(res);

	}



	void readShorts(short* data, int nOfShorts) throw (IOException) {

		buffer->setData(data, sizeof(short) * nOfShorts, false);

		int count = in->readFully(*buffer);

		if (count != (int)(sizeof(int) * nOfShorts)) {

			throw(IOException("LittleEndianDataInputStream::readFloats - not enough data", 

												__FILE__, __LINE__));

		}

	}


 private:

	/** Datenpuffer, Optimierung fuer readFloats etc. */
	DataBuffer* buffer;

};
