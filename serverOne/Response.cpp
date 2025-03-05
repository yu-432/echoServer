#include "Response.hpp"

#include <iostream>
#include <iterator>
#include <fstream>

#include "Header.hpp"
#include "config.hpp"

std::string Response::makeResponse(std::vector<std::string>& header,
                                   std::vector<std::string>& message_body) {
  std::string server_response;
  int header_size = header.size();
  int body_size = message_body.size();

  std::string tmp;

  for (int i = 0; i < header_size; i++) {
    server_response.append(header[i].c_str());
  }

  for (int i = 0; i < body_size; i++) {
    server_response.append(message_body[i].c_str());
  }
  return server_response;
}

std::vector<std::string>& Response::makeHeader(int version, int bodyLength,
                                               int isFileExist,
                                               std::string& path) {
  if (HTTP_VERSION == 1 && path != "") {
    return Header::makeResponse302(path);
  } else if (HTTP_VERSION == 2) {
    return Header::makeResponseUpgrade();
  } else if (isFileExist == 1) {
    return Header::makeResponse404();
  } else {
    return Header::makeResponse200(bodyLength);
  }

  static std::vector<std::string> response_header;
  return response_header;
}

void Response::makeBody(std::vector<std::string>& bodyContent,
                        int bodyContentLength, std::ifstream& outputFile) {
  if (outputFile.fail() != 0) {
    std::cout << "File was not found." << std::endl;
    return;
  }

  char readFileBuf[BUF_SIZE];
  outputFile.read(readFileBuf, BUF_SIZE);
  bodyContent.push_back(readFileBuf);
  bodyContentLength = outputFile.gcount();
}
