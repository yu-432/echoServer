#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include "Configure.hpp"

class Parser {
  public:
    static char* getFilename(const char* executive_file);
    static std::string arvgPathAnalyzer(std::string requestPath, const char* path, const char* executiveFile);
    static std::string getRequestlinePath(char buf[BUF_SIZE]);
};

#endif