#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
// #include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include "Configure.hpp"

class Socket {
  public:
    explicit Socket(int port) : _port(port) {};
    void set_listenfd();
    void set_sockaddr_in();
    int set_socket();
    int get_listenfd() const {return this->listenfd; }

  private:
    int listenfd;
    int _port;
    struct sockaddr_in servAddr;
};

#endif
