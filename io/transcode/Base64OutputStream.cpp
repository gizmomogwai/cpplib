#include <io/transcode/Base64OutputStream.h>

const char Base64OutputStream::table[64] = {
  // 0   1   2   3   4   5   6   7
    'A','B','C','D','E','F','G','H', // 0
    'I','J','K','L','M','N','O','P', // 1
    'Q','R','S','T','U','V','W','X', // 2
    'Y','Z','a','b','c','d','e','f', // 3
    'g','h','i','j','k','l','m','n', // 4
    'o','p','q','r','s','t','u','v', // 5
    'w','x','y','z','0','1','2','3', // 6
    '4','5','6','7','8','9','+','/'  // 7
};

void Base64OutputStream::write(int b) throw (IOException) {

  if (current >= 3) current = 0;
  data[current++] = (unsigned char)(b & 0xff);

  if (current == 3) {
    doWrite();
  }
}

void Base64OutputStream::doWrite() throw (IOException) {
  unsigned char a;
  unsigned char b;
  unsigned char c;
  // 3 byte collected .. write it
  if (current == 3) {
    a = data[0];
    b = data[1];
    c = data[2];
    out->write(table[(a >> 2) & 0x3F]);
    out->write(table[((a << 4) & 0x30) + ((b >> 4) & 0xf)]);
    out->write(table[((b << 2) & 0x3c) + ((c >> 6) & 0x3)]);
    out->write(table[c & 0x3F]);    
    bytesOutputted += 4;
    if (bytesOutputted >= 74) {
      bytesOutputted = 0;
      out->write(13);
      out->write(10);
    }
  } else if (current == 2) {
    a = data[0];
    b = data[1];
    c = 0;
    out->write(table[(a >> 2) & 0x3F]);
    out->write(table[((a << 4) & 0x30) + ((b >> 4) & 0xf)]);
    out->write(table[((b << 2) & 0x3c) + ((c >> 6) & 0x3)]);
    out->write('=');    
  } else if (current == 1) {
    a = data[0];
    b = 0;
    c = 0;
    out->write(table[(a >> 2) & 0x3F]);
    out->write(table[((a << 4) & 0x30) + ((b >> 4) & 0xf)]);
    out->write('=');
    out->write('=');    
  }
  
}

void Base64OutputStream::flush() throw (IOException) {
  if ((current == 1) || (current == 2)){
    doWrite();
  }
}
