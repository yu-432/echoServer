#include "Parser.hpp"

//実行ファイルパスを元に、ディレクトリパスを取得する関数
char* Parser::getFilename(const char* executiveFile) {
  int length = strlen(executiveFile);
  static char buf[BUF_SIZE];
  // sampleでは"/proc/self/exe"となっているがmacでは存在しないためgetcwdを仮に使用、失敗するかもしれない
  // readlink("/Users/yooshima/Documents/42cursus/echoServer/serverOne", buf, sizeof(buf)-1); //sample
  if (getcwd(buf, sizeof(buf)-1) == NULL)
    strcpy(buf, "./");
  int bufLength = strlen(buf);
  for (int i = 0; i <= length; i++) {
    buf[bufLength-i-1] = 0;
  }
  return buf;
}

//pathの解析
std::string Parser::argvPathAnalyzer(std::string requestPath, const char* path, const char* executiveFile) {
  std::string pathString;
  //pathがない場合
  if (strcmp(path, "") == 0) {
    if (requestPath == std::string("/")) {
      pathString = std::string(Parser::getFilename(executiveFile)) + std::string("/index.html");
    } else {
      int judge = requestPath.rfind(".", 20);
      if (judge >= 0) {
        pathString = std::string(Parser::getFilename(executiveFile)) + requestPath;
      } else {
        pathString = std::string(Parser::getFilename(executiveFile)) + requestPath + std::string("/index.html");
      }
    }
    //pathが存在する場合
  } else {
    int judge = requestPath.rfind(".", 20);
    if (judge >= 0) {
      pathString = std::string(path) + requestPath;
    } else {
      pathString = std::string(path) + requestPath + std::string("/index.html");
    }
  }
  return pathString;
}

//clientのリクエストから対象ディレクトリまでのpathを抜き取る
//一旦作り切ってbufの中身をみてみたい
std::string Parser::getRequestlinePath(char buf[BUF_SIZE]) {
  int spaceNum = 0;
  char pathBuf[64];
  int currentPoint = 0;
  std::string pathString;

  for (int i = 0; i < BUF_SIZE; i++) {
    if (spaceNum == 2) {
      pathBuf[currentPoint] = 0;
      pathString = std::string(pathBuf);
      return pathString;
    }
    if (spaceNum == 1) {
      if (buf[i] != ' ')
        pathBuf[currentPoint++] = buf[i];
    }
    if (buf[i] == ' ')
      ++spaceNum;
  }
  return "";
}
