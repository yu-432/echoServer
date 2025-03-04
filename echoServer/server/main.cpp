#include "Server.hpp"

// int c = 0;

// void* SendTask(void* arg) {
// (void)arg;
// Server* sock = (Server*)arg;
// while (true) {
// std::string text = "server->client" + std::to_string(c);
// c++;
// sock->SendText(text.c_str());
// std::this_thread::sleep_for(std::chrono::seconds(1));
// }
// }

void* RecvTask(void* arg) {
  Server* sock = (Server*)arg;
  while (true) {
    char buf[1024];
    sock->RecvText(buf);
    if (!std::strcmp(buf, "exit")) exit(0);
    std::cout << "Receive: " << buf << std::endl;
  }
}

int main(void) {
  Server server(8080);
  server.start();
  server.connect();

  // pthread_t threadSendId;
  pthread_t threadRecvId;
  // pthread_create(&threadSendId, NULL, SendTask, &server);
  pthread_create(&threadRecvId, NULL, RecvTask, &server);
  // pthread_join(threadSendId, NULL);
  pthread_join(threadRecvId, NULL);
}
