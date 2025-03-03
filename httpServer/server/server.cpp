// #include "Socket.hpp"
// #include "Configure.hpp"
// // #include <stdbool.h>

// int http() {
//   std::string executive_file = HTTP_FILE;
//   Socket *sock = new Socket(HTTP_PORT);
//   sock->set_socket();

//   // int body_length = 0;
//   // int is_file_exist;

//   int accfd = -1;

//   while (true) {
//     accfd = accept(sock->get_listenfd(), (struct sockaddr*)NULL, NULL);

//     if (accfd == -1) {
//       continue;
//     }
//     char buf[BUF_SIZE];
//     memset(buf, 0, sizeof(buf));
//     std::string recv_str = "";
//     ssize_t read_size = 0;

//     do {
//       read_size = recv(accfd, buf, sizeof(buf)-1, 0);
//       if (read_size == -1) {
//         std::cout << "read() failed" << std::endl;
//         std::cout << "ERROR: " << errno << std::endl;
//         close(accfd);
//         accfd = -1;
//         break;
//       }
//       if (read_size > 0) {
//         recv_str.append(buf);
//       }
//       if ((recv_str[recv_str.length()-4] == 0x0d) &&
//       (recv_str[recv_str.length()-3] == 0x0a) &&
//       (recv_str[recv_str.length()-2] == 0x0d) &&
//       (recv_str[recv_str.length()-1] == 0x0a)
//       ) {
//         break;
//       } 
//     } while (read_size > 0);
//   }
// }

// int main(void) {
//   std::cout << "hello" << std::endl;
//   http();
//   return 0;
// }


#include "Socket.hpp"
#include "Configure.hpp"
#include "Parser.hpp"
#include "Response.hpp"
#include <fstream>
#include <string.h>

int http() {
  std::string executive_file = HTTP_FILE;
  Socket *sock = new Socket(HTTP_PORT);
  
  if (sock->set_socket() < 0) {
    std::cout << "Failed to setup socket" << std::endl;
    delete sock;
    return -1;
  }
  
  std::cout << "Server started on port " << HTTP_PORT << std::endl;
  
  int accfd = -1;

  while (true) {
    std::cout << "Waiting for connection..." << std::endl;
    accfd = accept(sock->get_listenfd(), (struct sockaddr*)NULL, NULL);

    if (accfd == -1) {
      std::cout << "Accept failed: " << strerror(errno) << std::endl;
      continue;
    }
    
    std::cout << "Connection accepted" << std::endl;
    
    char buf[BUF_SIZE];
    memset(buf, 0, sizeof(buf));
    std::string recv_str = "";
    ssize_t read_size = 0;

    do {
      read_size = recv(accfd, buf, sizeof(buf)-1, 0);
      if (read_size == -1) {
        std::cout << "read() failed: " << strerror(errno) << std::endl;
        close(accfd);
        accfd = -1;
        break;
      }
      
      if (read_size > 0) {
        buf[read_size] = '\0';  // NULL終端を確実に
        recv_str.append(buf);
      }
      
      // HTTPリクエスト終了の検出（ヘッダー後の空行）
      if ((recv_str.length() >= 4) && 
          (recv_str[recv_str.length()-4] == 0x0d) &&
          (recv_str[recv_str.length()-3] == 0x0a) &&
          (recv_str[recv_str.length()-2] == 0x0d) &&
          (recv_str[recv_str.length()-1] == 0x0a)) {
        break;
      }
    } while (read_size > 0);
    
    if (accfd == -1) continue;  // readエラーがあった場合スキップ
    
    std::cout << "Received request: " << recv_str.substr(0, recv_str.find("\r\n")) << std::endl;
    
    // リクエストパスの取得
    std::string request_path = Parser::getRequestlinePath(const_cast<char*>(recv_str.c_str()));
    
    // ファイルパスの解析
    std::string file_path = Parser::arvgPathAnalyzer(request_path, "", executive_file.c_str());
    
    std::cout << "File path: " << file_path << std::endl;
    
    // ファイルの存在確認
    std::ifstream file(file_path.c_str());
    int is_file_exist = file.fail();
    
    // レスポンスボディの作成
    std::vector<std::string> body_content;
    int body_length = 0;
    
    if (!is_file_exist) {
      Response::makeBody(body_content, body_length, file);
      body_length = body_content[0].length();
    }
    
    // ヘッダーの作成
    std::vector<std::string>& header = Response::makeHeader(HTTP_VERSION, body_length, is_file_exist, "");
    
    // レスポンスの作成
    std::string response = Response::makeResponse(header, body_content);
    
    // レスポンスの送信
    send(accfd, response.c_str(), response.length(), 0);
    
    // 接続のクローズ
    close(accfd);
  }
  
  delete sock;  // メモリリーク防止
  return 0;
}

int main(void) {
  std::cout << "Starting server..." << std::endl;
  http();
  return 0;
}