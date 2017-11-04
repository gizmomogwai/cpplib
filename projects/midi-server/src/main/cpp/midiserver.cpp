#include <rtmidi/RtMidi.h>
#include <cstdlib>
#include <io/DataOutputStream.h>
#include <iostream>
#include <lang/Thread.h>
#include <net/ServerSocket.h>
#include <util/ListIterator.h>
#include <vector>

class Client {
public:
  Client(Socket* s)
      : dataOutputStream(new DataOutputStream(&s->getOutputStream(), false)),
        socket(s) {}

  ~Client() {
    delete dataOutputStream;
    delete socket;
  }

  void notify(unsigned char note, unsigned char volume) throw (IOException) {
    dataOutputStream->write(note);
    dataOutputStream->write(volume);
  }
  void notify(std::vector<unsigned char>& message) throw (IOException) {
    dataOutputStream->write((unsigned char)message.size());
    for (auto aByte : message) {
      dataOutputStream->write(aByte);
    }
  }

private:
  DataOutputStream* dataOutputStream;
  Socket* socket;
};

class Server {
public:
  Server() : serverSocket(55554) {}

  void send(std::vector<unsigned char>& message) {
    VectorIterator<Client*> i(&clients);
    while (i.hasNext()) {
      Client* client = i.next();
      try {
        client->notify(message);
      } catch (IOException& e) {
        std::cout << e.getMessage() << std::endl;
        i.remove();
        // delete client;
      } catch (...) {
        std::cout << "other exception" << std::endl;
      }
    }
  }

  void notifyClients(unsigned char pitch, unsigned char velocity) {
    std::cout << "Sending to " << clients.size() << " clients: " << (int)pitch
              << "@" << (int)velocity << std::endl;
    VectorIterator<Client*> i(&clients);
    while (i.hasNext()) {
      Client* client = i.next();
      try {
        client->notify(pitch, velocity);
      } catch (IOException& e) {
        std::cout << e.getMessage() << std::endl;
        i.remove();
        // delete client;
      } catch (...) {
        std::cout << "other exception" << std::endl;
      }
    }
  }

  void run() {
    while (true) {
      std::cout << "Waiting for client" << std::endl;
      Client* client = new Client(serverSocket.accept());
      std::cout << "One client connected" << std::endl;
      clients.push_back(client);
    }
  }

private:
  ServerSocket serverSocket;
  std::vector<Client*> clients;
};

void mycallback(double deltatime,
                std::vector<unsigned char>* message,
                void* userData) {
  Server* server = (Server*)userData;

  server->send(*message);

  unsigned int nBytes = message->size();
  for (unsigned int i = 0; i < nBytes; i++) {
    std::cout << "Byte " << i << " = 0x" << std::hex << (int)message->at(i) << ", ";
  }
  std::cout << std::endl;
  /*
  // https://www.cs.cmu.edu/~music/cmsip/readings/MIDI%20tutorial%20for%20programmers.html
  // http://fmslogo.sourceforge.net/manual/midi-table.html: Control Change	176 + Channel	64 Damper Pedal	0:off 127:on
  // http://computermusicresource.com/Control.Change.html - 176-191 64 0-127 Sustain Pedal
  // http://computermusicresource.com/MIDI.Commands.html - switch to hex
  if (nBytes == 3) {
    unsigned char status = message->at(0);
    if ((status & 0xf0) == 0x90) {
      // NOTE ON
      unsigned char pitch = (message->at(1) & 0x7f);
      unsigned char velocity = (message->at(2) & 0x7f);
      server->notifyClients(pitch, velocity);
    } else if ((status & 0xf0) == 0x10) {
      // NOTE OFF
      unsigned char pitch = (message->at(1) & 0x7f);
      server->notifyClients(pitch, 0);
    }
  }

  if (nBytes > 0) {
    std::cout << "stamp = " << deltatime << std::endl;
  }
  */
}
/*
class CallServer : public Runnable {
public:
  Server& server;
  CallServer(Server& s) : server(s) {}
  void run() {
    int note = 0;
    while (true) {
      server.notifyClients(note++, 100);
      Thread::sleep(1000);
    }
  }
};
*/
int main() {
  try {
    Server server;
    RtMidiIn midiin;

    unsigned int nPorts = midiin.getPortCount();
    std::cout << "port count " << nPorts << std::endl;
    if (nPorts == 0) {
      std::cout << "No ports available!\n";
      return 0;
    }

    int port = 0;
    for (int i=0; i<nPorts; ++i) {
      std::cout << "Port " << i << " " << midiin.getPortName(i) << std::endl;
      if (midiin.getPortName(i).find("USB-MIDI") != std::string::npos) {
	port = i;
      }
    }
    midiin.openPort(port);
    midiin.setCallback(&mycallback, &server);
    midiin.ignoreTypes(false, false, false);

    server.run();
  } catch (Exception& e) {
    std::cout << "problem: " << e.getMessage() << std::endl;
    return 1;
  }
  return 0;
}
