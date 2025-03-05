#include "Socket.hpp"
#include <unistd.h>

void Socket::setListenSock() {
  //SOCK_STREAM tcp
  //AF_INET ipv4
  _listenSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (_listenSocket == -1) {
    std::cout << "socket() failed." << std::endl;
    exit(1);
  }
}

void Socket::setSockaddrIn() {
  memset(&this->_servAddr, 0 , sizeof(this->_servAddr));

  this->_servAddr.sin_family = AF_INET;
  //全てのネットワークインタフェースで指定したポートへの接続を受け付け  
  this->_servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  //指定ポートの設定
  this->_servAddr.sin_port = htons(this->_port);
}

int Socket::setSocket() {
  //socketの生成
  Socket::setListenSock();
  int optval = 1;
  //socketのオプション設定
  if (setsockopt(_listenSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
    std::cout << "setsockopt() failed." << std::endl;
    close(_listenSocket);
    return -1;
  }
  //_servAddr初期化 IPアドレスやポート番号を保持している
  Socket::setSockaddrIn();
  //生成したsocketに_servAddrを割り当て通信可能状態にする
  if (bind(_listenSocket, (struct sockaddr*)&_servAddr, sizeof(_servAddr)) == -1) {
    std::cout << "bind() failed." << std::endl;
    return -1;
  }
  //ソケットを接続待ち状態にする
  //SOMAXCONN 最大接続キュー
  if (listen(_listenSocket, SOMAXCONN) == -1) {
    std::cout << "listen() failed." << std::endl;
    close(_listenSocket);
    return -1;
  }

  return 0;
}