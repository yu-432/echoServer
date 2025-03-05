#ifndef HEADER_HPP
#define HEADER_HPP

#include <vector>

class Header {
  public:
    static std::vector<std::string>& makeResponse404();
    static std::vector<std::string>& makeResponse200(int bodyLength);
    static std::vector<std::string>& makeResponse302(std::string path);
    static std::vector<std::string>& makeResponseUpgrade();
};

#endif