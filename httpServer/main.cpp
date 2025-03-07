#include "Socket.hpp"
#include "Parser.hpp"
#include "config.hpp"
#include "Response.hpp"
#include <fstream>
#include <string>

int http() {
  std::string filePath = HTML_DIR;
  Socket* sock = new Socket(SERVER_PORT);
  sock->setSocket();

  int bodyLength = 0;
  int isFileExist;

  int accFd = -1;

  while (true) {
    // sock宛の接続要求が入っているキューの先頭から取り出し、接続用のソケットを作成。そのソケットを指すfdを返す
    accFd = accept(sock->getListenFd(), (struct sockaddr*)NULL, NULL);
    if (accFd == -1) continue;
    
    char buf[BUF_SIZE];
    memset(buf, 0, sizeof(buf));
    std::string recvStr = "";
    std::size_t readSize = 0;
    
    do {
      //ソケットfdからメッセージを受け取る
      readSize = recv(accFd, buf, sizeof(buf)-1, 0);
      if (readSize == -1) {
        std::cout << "read() failed." << std::endl;
        std::cout << "ERROR: " << errno << std::endl;
        close(accFd);
        accFd = -1;
        break;
      }

      // if (readSize == 0) {
      //   std::cout << "Client closed connection" << std::endl;
      //   close(accFd);
      //   accFd = -1;
      //   break;
      // }
      std::cout << buf << std::endl;

      std::cout << "Received " << readSize << "bytes" << std::endl;
      // buf[readSize] = '\0';
      if (readSize > 0)
        recvStr.append(buf);

      //HTTP通信では、リクエストヘッダーとボディの間に空行（CR+LF+CR+LF）が挿入される。その空行を探す操作
      if ((recvStr[recvStr.length()-4] == 0x0d) &&
      (recvStr[recvStr.length()-3] == 0x0a) &&
      (recvStr[recvStr.length()-2] == 0x0d) &&
      (recvStr[recvStr.length()-1] == 0x0a)) {
        break;
      }
    } while (readSize > 0);
    std::cout << "Recv process finish" << std::endl;

    std::string path = "";
    std::string pathString = "";
    std::string exe = filePath;// "www"
    std::size_t pos = exe.rfind('/');
    if (pos != std::string::npos)
      exe = exe.substr(pos + 1);
    pathString.clear(); //必要？
    //リクエストから対象までのpathを抜き取る
    path = Parser::getRequestlinePath(buf);
    //pathの解析
    pathString = Parser::argvPathAnalyzer(path, filePath.c_str(), exe.c_str());
    std::cout << "path string: " << pathString << std::endl;

    std::cout << "hello" << std::endl;
    //取得したpathのファイルを開き内容を取得する
    std::ifstream outputFile(pathString.c_str());
    char line[256];
    //stream作成に失敗した場合
    isFileExist = outputFile.fail();
    bodyLength = 0;
    //ファイルの中身を読み取り、vectorに保存する
    std::vector<std::string> messageBody;
    while (outputFile.getline(line, 256-1)) {
      bodyLength += strlen(line);
      messageBody.push_back(std::string(line));
    }

    // recvStr.append(buf);
    //HTTPレスポンスの作成
    std::string serverResponse;
    std::vector<std::string> header = Response::makeHeader(3,  bodyLength, isFileExist, path);
    serverResponse = Response::makeResponse(header, messageBody);
    std::cout << serverResponse << std::endl;
    //
    //
    //
    //ここが失敗しているみたい
    std::cout <<"send prev" << accFd << serverResponse << std::endl;
    if (send(accFd, serverResponse.c_str(), serverResponse.length(), 0) == -1)
      std::cout << "write() failed" << std::endl;

    outputFile.close();
    close(accFd);
    accFd = -1;
  }
  close(sock->getListenFd());
  return 0;
}

int main(void) {
  http();
  return 0;
}