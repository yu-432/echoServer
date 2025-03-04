#include "Server.hpp"

Server::Server(int port) : _serverSocket(0) {
  std::cout << "Server constructor: " << port << std::endl;
  _addr_server.sin_addr.s_addr = INADDR_ANY;
  _addr_server.sin_port = htons(port);
  // htons 関数を使用して、ホストのバイト順の IP ポート番号をネットワーク
  // バイト順の IP ポート番号に変換できます。
  _addr_server.sin_family = AF_INET;
  // AF_INET は、IPv4
  // インターネットプロトコルを使用することを示すために使用されます。
}

Server::~Server() {}

void Server::start() {
  std::cout << "Server start" << std::endl;
  _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  // SOCK_STREAM は、TCP/IP プロトコル
  //  エンドポイントの作成、ソケットはfdとして扱われる
  //   AF_INET は、IPv4
  bind(_serverSocket, (sockaddr*)&_addr_server, sizeof(_addr_server));
  // ソケットにアドレスを割り当てる
  listen(_serverSocket, SOMAXCONN);
  // ソケットを接続待ち状態にする
  socklen_t socklen = sizeof(_addr_client);
  // アドレス構造体のサイズを取得
  _clientSocket = accept(_serverSocket, (sockaddr*)&_addr_client, &socklen);
  // クライアントからの接続を受け入れる
}

void Server::SendText(const char* text) {
  send(_clientSocket, text, std::strlen(text), 0);
}

void Server::RecvText(char* text) {
  int recv_size = recv(_clientSocket, text, 1024, 0);
  text[recv_size] = '\0';
}

void Server::connect() { std::cout << "Server connect" << std::endl; }