#include <io/zip/CRC32.h>

#include <assert.h>
#include <zlib.h>

CRC32::CRC32() {
	reset();	
}

CRC32::~CRC32() {
	
}

void CRC32::update(int b) {
//	assert(b != -1);
	
	unsigned char help = b & 0xff;
	crc = crc32(crc, &help, 1);
}

void CRC32::update(DataBuffer* b, int offset, int length) {
	unsigned char* buffer = (unsigned char*)(b->getData(offset));
	crc = crc32(crc, buffer, length);
}


