#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <vector>

class Response {
  public:
    static std::string makeResponse(std::vector<std::string>& header, std::vector<std::string>& messageBody);
    static std::vector<std::string>& makeHeader(int version, int bodyLength, int isFileExist, std::string& path);
    static void makeBody(std::vector<std::string>& bodyContent, int bodyContentLength, std::ifstream& outputFile);
};

#endif
