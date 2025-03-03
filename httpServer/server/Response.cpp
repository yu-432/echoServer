#include "Response.hpp"
#include "Configure.hpp"

std::string Response::makeResponse(std::vector<std::string>& header, std::vector<std::string>& messageBody) {
  std::string serverResponse;
  int headerSize = header.size();
  int bodySize = messageBody.size();

  for (int i = 0; i < headerSize; i++) {
    serverResponse.append(header[i].c_str());
  }

  for (int i = 0; i < bodySize; i++) {
    serverResponse.append(messageBody[i].c_str());
  }
  return serverResponse;
}

std::vector<std::string>& Response::makeHeader(int version, int body_length, int is_file_exist, std::string path) {
  if (HTTP_VERSION == 1 && path != "") {
      return HttpHeader::make_response302(path);
  }
  else if (HTTP_VERSION == 2) {
      return HttpHeader::make_responseUpgrade();
  }
  else if (is_file_exist == 1) {
      return HttpHeader::make_response404();
  }
  else {
      return HttpHeader::make_response200(body_length);
  }

  static std::vector<std::string> response_header;
  return response_header;
}

void Response::makeBody(std::vector<std::string>& bodyContent, int bodyContentLength, std::ifstream& outputFile) {
  if (outputFile.fail() != 0) {
    std::cout << "File was not found. " << strerror(errno)<< std::endl;
    return ;
  }
  std::cout << "makebody find file" << std::endl;
  char readFileBuf[BUF_SIZE];
  outputFile.read(readFileBuf, BUF_SIZE);
  bodyContent.push_back(readFileBuf);
  bodyContentLength = outputFile.gcount();
}
