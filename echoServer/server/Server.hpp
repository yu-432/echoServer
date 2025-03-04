#ifndef SERVER_HPP
#define SERVER_HPP

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cstring>
#include <iostream>
#include <thread>

class Server {
 public:
  Server(int port);
  ~Server();

  void start();
  void connect();
  void SendText(const char* text);
  void RecvText(char* text);

 private:
  int _serverSocket;
  int _clientSocket;
  struct sockaddr_in _addr_server;
  struct sockaddr_in _addr_client;
};

#endif