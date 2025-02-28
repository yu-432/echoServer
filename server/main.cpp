#include "Server.hpp"

int c = 0;

void SendTask(Server* sock) {
  while (true) {
    std::string text = "server->client" + std::to_string(c);
    c++;
    sock->SendText(text.c_str());
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void RecvTask(Server* sock) {
  while (true) {
    char buf[1024];
    sock->RecvText(buf);
    std::cout << "Receive: " << buf << std::endl;
  }
}

int main(void) {
  Server server(8080);
  server.start();
  server.connect();

  std::thread thread_send(SendTask, &server);
  std::thread thread_recv(RecvTask, &server);
  thread_send.join();
  thread_recv.join();
}
