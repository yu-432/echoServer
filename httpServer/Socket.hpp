#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <netinet/in.h>
#include <iostream>

class Socket {
 public:
  explicit Socket(int port) : _port(port) {};
  void setListenSock();
  void setSockaddrIn();
  int setSocket();

  int getListenFd() const { return _listenSocket; };

 private:
  int _port;
  int _listenSocket;
  struct sockaddr_in _servAddr;
};

#endif
