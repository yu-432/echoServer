#include "Client.hpp"

#include <arpa/inet.h>

Client::Client(const char* ip_server, int port_server)
    : _socket(0), _sockaddr_len(sizeof(struct sockaddr_in)) {
  _addrServer.sin_addr.s_addr = inet_addr(ip_server);
  // inet_addr 関数を使用して、ドット形式の IP
  // アドレスをネットワークバイト順のバイナリ形式に変換
  _addrServer.sin_port = htons(port_server);
  // htons 関数を使用して、ホストのバイト順の IP
  // ポート番号をネットワークバイト順の IP ポート番号に変換
  _addrServer.sin_family = AF_INET;
  // AF_INET は、IPv4
}

Client::~Client() {}

void Client::Connect() {
  _socket = socket(AF_INET, SOCK_STREAM, 0);
  // エンドポイントの作成、ソケットはfdとして扱われる
  // SOCK_STREAM は、TCP/IP プロトコル
  connect(_socket, (struct sockaddr*)&_addrServer, _sockaddr_len);
  // サーバーに接続
}

void Client::SendText(const char* text) {
  send(_socket, text, std::strlen(text), 0);
}

void Client::RecvText(char* text) {
  std::size_t recv_size = recv(_socket, text, 1024, 0);
  text[recv_size] = '\0';
}