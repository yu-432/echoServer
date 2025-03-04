#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../server/Server.hpp"

class Client {
 public:
  Client(const char* ip_server, int port_server);
  ~Client();
  void Connect();
  void SendText(const char* text);
  void RecvText(char* text);

 private:
  int _socket;
  int _sockaddr_len;
  struct sockaddr_in _addrServer;
};

#endif