#include "Parser.hpp"
#include <iostream>
#include <unistd.h>

char *Parser::getFilename(const char* executiveFile) {
  static char buf[BUF_SIZE] = {};
  // readlink("/proc/self/exe", buf, sizeof(buf)-1);

  getcwd(buf, sizeof(buf));
  std::cout << "cwd: " << buf << std::endl;
  int buf_length = strlen(buf);
  int length = strlen(executiveFile);
  std::cout << "getFilename prev: " << buf << std::endl;
  for (int i = 0; i <= length; i++) {
    buf[buf_length-i-1] = 0;
  }
  std::cout << "getFilename after: " <<buf << std::endl;
  return buf;
}

std::string Parser::arvgPathAnalyzer(std::string requestPath, const char* path, const char* executiveFile) {
  std::string pathString;
  if (strcmp(path, "") == 0) {
    if (requestPath == std::string("/")) {
      pathString = std::string(Parser::getFilename(executiveFile)) + std::string("index.html");
    }
    else {
      int judge = requestPath.rfind(".", 20);
      if (judge >= 0) {
        pathString = std::string(Parser::getFilename(executiveFile)) + requestPath;
      } else {
        pathString = std::string(Parser::getFilename(executiveFile)) + requestPath + std::string("/index.html");
      }
    }
  }
  else {
    int judge = requestPath.rfind(".", 20);
    if (judge >= 0) {
      pathString = std::string(path) + requestPath;
    } else {
      pathString = std::string(path) + requestPath + std::string("/index/html");
    }
  }
  return pathString;
}

std::string Parser::getRequestlinePath(char buf[BUF_SIZE]) {
  int spaceNum = 0;
  char pathBuffer[32];
  int currentPoint = 0;
  std::string pathString;
  for(int i = 0; i < BUF_SIZE; i++) {
    if (spaceNum == 2) {
      pathBuffer[currentPoint] = 0;
      pathString = std::string(pathBuffer);
      return pathString;
    }
    if (spaceNum == 1) {
      if (buf[i] != ' ') {
        pathBuffer[currentPoint++] = buf[i];
      }
    }
    if (buf[i] == ' ') {
      ++spaceNum;
    }
  }
  return "";
}