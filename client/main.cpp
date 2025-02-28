#include "Client.hpp"

int count = 0;

void SendTask(Client* sock) {
  while (true) {
    std::string test =
        "hello, this is client. to server" + std::to_string(count);
    count++;
    sock->SendText(test.c_str());
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void RecvTask(Client* sock) {
  while (true) {
    char buf[1024];
    sock->RecvText(buf);
    std::cout << "Receive: " << buf << std::endl;
  }
}

int main(void) {
  std::cout << "Client start" << std::endl;
  int port_server = 8080;
  const char* ip_server = "127.0.0.1";
  Client client(ip_server, port_server);
  client.Connect();
  std::thread thread_send(SendTask, &client);
  std::thread thread_recv(RecvTask, &client);
  thread_send.join();
  thread_recv.join();
}