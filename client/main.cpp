#include "Client.hpp"

int count = 0;

void* SendTask(void* arg) {
  Client* sock = (Client*)arg;
  while (true) {
    std::string test =
        "hello, this is client. to server" + std::to_string(count);
    count++;
    sock->SendText(test.c_str());
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void* RecvTask(void* arg) {
  Client* sock = (Client*)arg;
  while (true) {
    char buf[1024];
    sock->RecvText(buf);
    std::cout << "Receive: " << buf << std::endl;
  }
}

int main(void) {
  std::cout << "Client start" << std::endl;
  pthread_t threadSendId;
  pthread_t threadRecvId;
  int port_server = 8080;
  const char* ip_server = "127.0.0.1";
  Client client(ip_server, port_server);
  client.Connect();
  pthread_create(&threadSendId, NULL, SendTask, &client);
  pthread_create(&threadRecvId, NULL, RecvTask, &client);
  pthread_join(threadSendId, NULL);
  pthread_join(threadRecvId, NULL);
}