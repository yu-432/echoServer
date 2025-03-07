#ifndef PARSER_HPP
#define PARSER_HPP

#include "config.hpp"
#include <iostream>
#include <unistd.h>

class Parser {
  public:
    static char* getFilename(const char* executiveFile);
    static std::string argvPathAnalyzer(std::string requestPath, const char* path, const char* executiveFile);
    static std::string getRequestlinePath(char buf[BUF_SIZE]);
};

#endif