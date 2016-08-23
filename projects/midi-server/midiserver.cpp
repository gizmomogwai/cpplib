#include <RtMidi.h>
#include <cstdlib>
#include <iostream>

void mycallback(double deltatime, std::vector<unsigned char>* message,
                void* userData) {
  unsigned int nBytes = message->size();
  for (unsigned int i = 0; i < nBytes; i++) {
    std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
  }

  if (nBytes > 0) {
    std::cout << "stamp = " << deltatime << std::endl;
  }
}

int main() {
  RtMidiIn midiin;

  unsigned int nPorts = midiin.getPortCount();
  if (nPorts == 0) {
    std::cout << "No ports available!\n";
    return 0;
  }

  midiin.openPort(0);
  int i = 1;
  midiin.setCallback(&mycallback, &i);
  midiin.ignoreTypes(false, false, false);
  std::cout << "\nReading MIDI input ... press <enter> to quit.\n";

  char input;
  std::cin.get(input);

  return 0;
}
