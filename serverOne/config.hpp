#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <unistd.h>

const int BUF_SIZE = 1024;
const int SERVER_PORT = 8080;
const int HTTP_VERSION = 1;
const std::string HTML_DIR = "www";

#endif

// constグローバル宣言以外の方法がないか考える