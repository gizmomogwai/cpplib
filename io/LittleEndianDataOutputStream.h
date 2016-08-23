#pragma once

#include <io/DataOutputStream.h>

/** LittleEndianDataOutputStream, gibt Daten in LittleEndian aus.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-13, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/06/05 10:02:40 $
 *
 * @author cK, $Author: koestlin $
 */
class LittleEndianDataOutputStream : public DataOutputStream {

 public:
	/** Erzeugt einen neuen LittleEndianDataOutputStream.
	 *
	 * @param out Unterliegender OutputStream.
	 * @param handleStream soll der stream verwaltet werden.
	 */
	LittleEndianDataOutputStream(OutputStream* out,	bool handleStream) 
		: DataOutputStream(out, handleStream), 
		buffer(new DataBuffer(0, 0, false)) {
	}
		
	/** Raeumt auf. */
	virtual ~LittleEndianDataOutputStream() {
		delete(buffer);
	}
	
	void writeInt(int v) throw (IOException) {
		buffer->setData(&v, sizeof(int), false);
		out->write(buffer);
	}
		
	void writeInts(int* data, int length) throw (IOException) {
		buffer->setData(data, sizeof(int) * length, false);
		out->write(buffer);
	}
		
	void writeShort(short v) throw (IOException) {
		buffer->setData(&v, sizeof(short), false);
		out->write(buffer);
	}

	void writeShorts(short* data, int length) throw (IOException) {
		buffer->setData(data, sizeof(short) * length, false);
		out->write(buffer);
	}

	void writeUnsignedShort(unsigned short v) throw (IOException) {
		buffer->setData(&v, sizeof(unsigned short), false);
		out->write(buffer);
	}

	void writeUnsignedShorts(unsigned short* data, int length) throw (IOException) {
		buffer->setData(data, sizeof(unsigned short) * length, false);
		out->write(buffer);
	}

	void writeDouble(double v) throw (IOException) {
		buffer->setData(&v, sizeof(unsigned short), false);
		out->write(buffer);
	}
		
	void writeDoubles(double* data, int length) throw (IOException) {
		buffer->setData(data, sizeof(double) * length, false);
		out->write(buffer);
	}

	void writeFloat(float v) throw (IOException) {
		buffer->setData(&v, sizeof(float), false);
		out->write(buffer);
	}
		
	void writeFloats(float* data, int length) throw (IOException) {
		buffer->setData(data, sizeof(float) * length, false);
		out->write(buffer);
	}
		
		
 private:
	/** Datenpuffer. */
	DataBuffer* buffer;		
	
};
