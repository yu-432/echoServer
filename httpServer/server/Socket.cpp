#include "Socket.hpp"

void Socket::set_listenfd() {
  this->listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->listenfd == -1) {
    std::cout << "socket() failed" << std::endl;
    exit(1);
  }
}

void Socket::set_sockaddr_in() {
  memset(&this->servAddr, 0, sizeof(this->servAddr));

  this->servAddr.sin_family = AF_INET;
  this->servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  this->servAddr.sin_port = htons(this->_port);
}

int Socket::set_socket() {
  Socket::set_listenfd();
  
  int optval = 1;
  if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))== -1) {
    std::cout << "setsocketopt() failed" << std::endl;
    close(this->listenfd);
    return -1;
  }

  Socket::set_sockaddr_in();
  if (bind(this->listenfd, (struct sockaddr*)&this->servAddr, sizeof(this->servAddr)) == -1) {
    std::cout << "bind() failed" << strerror(errno) << std::endl;
    close(this->listenfd);
    return -1;
  }

  if (listen(this->listenfd, SOMAXCONN) == -1) {
    std::cout << "listen() failed" << std::endl;
    close(this->listenfd);
    return -1;
  }
  return 0;
}