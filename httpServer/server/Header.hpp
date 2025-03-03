#ifndef HEADER_HPP
#define HEADER_HPP

#include <map>
#include <sstream>
#include <string>
#include <vector>

class HttpHeader {
 public:
  static std::vector<std::string>& make_response404();
  static std::vector<std::string>& make_response200(int body_length);
  static std::vector<std::string>& make_response302(std::string path);
  static std::vector<std::string>& make_responseUpgrade();
};

#endif
